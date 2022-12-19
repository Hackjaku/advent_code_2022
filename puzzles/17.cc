
#include <algorithm>
#include <array>
#include <boost/tokenizer.hpp>
#include <cstddef>
#include <cassert>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <regex>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string_view>
#include <tuple>
#include <cassert>

// Types
using Coordinate = std::pair<std::int32_t, std::int32_t>;
using Shape = std::set<Coordinate>;
using Level = std::bitset<7>;
using Field = std::vector<Level>;

// Shapes
const static auto s_Shapes = std::array<Shape, 5> {{
    { Coordinate { 3, 3 }, Coordinate { 4, 3 }, Coordinate { 5, 3 }, Coordinate { 6, 3 } },                      // "-"
    { Coordinate { 4, 5 }, Coordinate { 3, 4 }, Coordinate { 4, 4 }, Coordinate { 5, 4 }, Coordinate { 4, 3 } }, // "+"
    { Coordinate { 3, 3 }, Coordinate { 4, 3 }, Coordinate { 5, 3 }, Coordinate { 5, 4 }, Coordinate { 5, 5 } }, // "mirrored L"
    { Coordinate { 3, 3 }, Coordinate { 3, 4 }, Coordinate { 3, 5 }, Coordinate { 3, 6 } },                      // "I"
    { Coordinate { 3, 3 }, Coordinate { 4, 3 }, Coordinate { 3, 4 }, Coordinate { 4, 4 } }                       // square
}};

// Used to add the global initial height, or decrease the height (by adding "-1")
auto operator+(const Shape& a_Shape, std::int32_t a_YPos) noexcept {
    auto l_NewShape = Shape {};
    for (const auto& l_Coordinate: a_Shape) {
        const auto& [l_X, l_Y] = l_Coordinate;
        l_NewShape.insert(Coordinate { l_X, (l_Y + a_YPos) } );
    } // for
    
    return l_NewShape;
}

// Move a piece left or right
[[nodiscard]] auto BlowPiece(Shape a_Piece, bool a_bToLeft) noexcept {
    auto l_MovedPiece = Shape {};
    for (const auto& l_Coordinate: a_Piece) {
        const auto& [l_X, l_Y] = l_Coordinate;
        auto l_XDelta = (a_bToLeft) ? -1 : 1;
        l_MovedPiece.insert(Coordinate { (l_X + l_XDelta), l_Y } );
    } // for
    
    return l_MovedPiece; // may return an out-of-bounds piece!
}

// Check if a given piece fits into the playing field
bool Fits(const Field& a_Field, const Shape& a_Piece) noexcept {
    for (const auto& l_Coordinate: a_Piece) {
        const auto& [l_X, l_Y] = l_Coordinate;
        if ((l_X < 1) || (l_X > 7)) return false; // out of bounds
        if (l_Y < 0) return false; // below base line
        if (l_Y < a_Field.size()) {
            const auto& l_Line = a_Field[l_Y];
            if (l_Line.test(l_X - 1)) {
                return false; // collision with an already settled piece
            } // if
        } // if
    } // for
    
    return true;
}

// Permanently add a piece, which moved to its final position, to the playing field
void Settle(Field& a_Field, const Shape& a_Piece) noexcept {
    for (const auto& l_Coordinate: a_Piece) {
        const auto& [l_X, l_Y] = l_Coordinate;
        while (a_Field.size() <= l_Y) {
            a_Field.push_back({});
        } // while
        
        a_Field[l_Y].set(l_X - 1);
    } // for
}

void Play(std::string_view a_FileName) noexcept {
    // Read wind movement information
    std::cout << std::endl << "Reading wind movement information from file \"" << a_FileName << "\"" << std::endl;
    std::ifstream l_InputStream { std::string { a_FileName } };
    std::string l_WindData;
    const auto l_ReadResult = static_cast<bool>(std::getline(l_InputStream, l_WindData));
    assert(l_ReadResult);
    
    auto l_Field = Field{};
    auto l_FieldDubDet = Field{};
    
    auto l_HeightA = std::uint64_t { 0 };
    
    const auto l_DetectorMaxWindow = 10000;
    auto l_DetectedCycle = std::uint64_t { 0 };
    auto l_DetectedCycleMod = std::uint64_t { 0 };
    
    auto l_DeltaSteps = std::uint64_t { 0 };
    auto l_DeltaSize1 = std::uint64_t { 0 };
    auto l_DeltaSize2 = std::uint64_t { 0 };
    
    auto l_WindIndex = 0;
    auto l_ShapeIndex = 0;
    auto l_PiecesDropped = std::uint64_t { 0 };
    while (l_PiecesDropped < (3 * l_DetectorMaxWindow)) { // wait one window for settlement, then two more for maximum matching
        if (l_PiecesDropped == 2022) {
            l_HeightA = l_Field.size();
        } else if (l_PiecesDropped == (2 * l_DetectorMaxWindow)) {
            l_FieldDubDet = l_Field;
        } else if ((!l_DetectedCycle) && (l_PiecesDropped > (2 * l_DetectorMaxWindow))) {
            if (std::memcmp(&l_Field[l_Field.size() - l_DetectorMaxWindow],
                            &l_FieldDubDet[l_FieldDubDet.size() - l_DetectorMaxWindow],
                            l_DetectorMaxWindow * sizeof(Level)) == 0) {
                l_DetectedCycle = (l_PiecesDropped - (2 * l_DetectorMaxWindow));
                l_DetectedCycleMod = (1000000000000 % l_DetectedCycle);
            } // if
        } else if (l_DetectedCycle && (!l_DeltaSize1) && ((l_PiecesDropped % l_DetectedCycle) == l_DetectedCycleMod)) {
            // Cycle known
            l_DeltaSize1 = l_Field.size();
        } else if (l_DetectedCycle && l_DeltaSize1 && (!l_DeltaSteps) && ((l_PiecesDropped % l_DetectedCycle) == l_DetectedCycleMod)) {
            l_DeltaSteps = l_PiecesDropped;
            l_DeltaSize2 = l_Field.size();
            break;
        } // else if
        
        auto l_Piece1 = s_Shapes[l_ShapeIndex] + l_Field.size(); // Spawn new piece
        assert(Fits(l_Field, l_Piece1));
        
        while (true) {
            // Manipulate one falling object
            const auto l_Piece2 = BlowPiece(l_Piece1, l_WindData[l_WindIndex] == '<');
            const auto l_Piece3 = Fits(l_Field, l_Piece2) ? l_Piece2 : l_Piece1;
            const auto l_Piece4 = (l_Piece3 + (-1));            
            if ((++l_WindIndex) == l_WindData.size()) {
                l_WindIndex = 0;
            } // if
        
            if (!Fits(l_Field, l_Piece4)) {
                Settle(l_Field, l_Piece3);
                break;
            } else  {
                l_Piece1 = l_Piece4;
            } // else
        } // while
    
        if (++l_ShapeIndex == s_Shapes.size()) {
            l_ShapeIndex = 0;
        } // if
        
        ++l_PiecesDropped;
    } // while
    
    std::cout << "A: height = " << l_HeightA << std::endl;
    std::cout << "B: height = " << ((((1000000000000 - l_DeltaSteps) / l_DetectedCycle) * (l_DeltaSize2 - l_DeltaSize1)) + l_DeltaSize2) << std::endl;
}

int main(int argc, char **argv) {
    Play("../inputs/17_test.txt");
    Play("../inputs/17.txt");
}