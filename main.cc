
#pragma GCC optimize("O3,inline,omit-frame-pointer,unroll-loops")
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstring>

using namespace std;

class SensorBeaconPair {
public:

    int sensorRow;
    int sensorCol;
    int beconRow;
    int beconCol;
    int mDist;

    int calmDist() {
        return abs(sensorCol - beconCol) + abs(sensorRow - beconRow);
    }

};


size_t split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

    return strs.size();
}



int main()
{

    string line;
    ifstream myfile; 

    vector<SensorBeaconPair> pairs;

    myfile.open("../inputs/15.txt");
    // int row = 2000000; // 10;
    // int minCol = -3909820; //-5;
    // int maxCol = 49372790; //25;

    // PART 2
    int minCol = 0;
    int maxCol = 4000000; //20;
    int minRow = minCol;
    int maxRow = maxCol;

    while ( getline (myfile,line) ) {


        vector<string> s;
        vector<string> ss;
        SensorBeaconPair sbp;

        split(line,s,' ');
        split(s[0],ss,',');
        sbp.sensorRow = stoi(ss[1]);
        sbp.sensorCol = stoi(ss[0]);

        split(s[1],ss,',');
        sbp.beconRow = stoi(ss[1]);
        sbp.beconCol = stoi(ss[0]);
        sbp.mDist = sbp.calmDist();

        pairs.push_back(sbp);

    }

    // PART 1
//    int n = 0;
//    for (int c = minCol; c<=maxCol; c++) {
//        int r = row;
//        for (SensorBeaconPair sbp : pairs) {
//            int dist = abs(sbp.sensorCol - c) + abs(sbp.sensorRow - r);
//            if (dist <= sbp.mDist()) {
//                // check if there is a sensor or beacon there
//                bool found = false;
//                for (SensorBeaconPair sb : pairs) {
//                    if (sb.beconCol == c && sb.beconRow == r) { found = true;}
//                    if (sb.sensorCol == c && sb.sensorRow == r) { found = true;}
//                }
//                if (!found) {n++;}
//                break;
//            }
//        }
//       // cerr << r << "," << c << " " << n << endl;
//    }
//    cout << n << endl;

    // PART 2
    for (int c = minCol; c<=maxCol; c++) {       
        for (int r = minRow; r<=maxRow; r++) {

            // check if there is a sensor or beacon there
            bool found = false;
            for (SensorBeaconPair sb : pairs) {
                if (sb.beconCol == c && sb.beconRow == r) { found = true;}
                if (sb.sensorCol == c && sb.sensorRow == r) { found = true;}
            }
            if (!found) {
                bool possibleLocation = true;
                for (SensorBeaconPair sbp : pairs) {
                    int dist = abs(sbp.sensorCol - c) + abs(sbp.sensorRow - r);
                    if (dist <= sbp.mDist) {
                        possibleLocation = false;   
                        // To speed up, we can jump over some rows   
                        r = sbp.sensorRow + sbp.mDist - abs( sbp.sensorCol - c ) ;
                        break;
                    }
                }
                if (possibleLocation && c>0 ) {      
                    long long freq = 4000000 * (long long)c + (long long)r;
                    cout << freq << endl;
                }
            }
        }
    }

    myfile.close();

}






