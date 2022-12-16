#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>

using namespace std;

class TunnelNode {
public:
    string name;
    int flow_rate;
    vector<TunnelNode*> connections;
    vector<string> opened;

    void add_connection(TunnelNode* node);
    int get_subtree_max_rate(int);
};

TunnelNode* get_node_by_name(vector<TunnelNode*> nodes, string name) {
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i]->name == name) {
            return nodes[i];
        }
    }
    return NULL;
}

int main() {
    fstream data("../inputs/16.txt", ios::in);
    
    string line;
    vector<TunnelNode*> nodes;

    while(getline(data, line)) {
        std::istringstream iss(line);
        string s;
        if (!(iss >> s)) { 
            break;
        }
        vector<string> tokens;
        boost::split(tokens, line, boost::is_any_of(";"), boost::token_compress_on);
        vector<string> node_info;
        boost::split(node_info, tokens[0], boost::is_any_of(" "), boost::token_compress_on);

        TunnelNode* node = new TunnelNode();
        node->name = node_info[0];
        node->flow_rate = stoi(node_info[1]);
        nodes.push_back(node);
    }

    data.clear();
    data.seekg(0, ios::beg);
    while(getline(data, line)) {
        std::istringstream iss(line);
        string s;
        if (!(iss >> s)) { 
            break;
        }
        vector<string> tokens;
        boost::split(tokens, line, boost::is_any_of(";"), boost::token_compress_on);
        vector<string> node_info;
        boost::split(node_info, tokens[0], boost::is_any_of(" "), boost::token_compress_on);
        vector<string> connections;
        boost::split(connections, tokens[1], boost::is_any_of(" "), boost::token_compress_on);

        TunnelNode* node = get_node_by_name(nodes, node_info[0]);
        for (int i = 0; i < connections.size(); i++) {
            TunnelNode* connection = get_node_by_name(nodes, connections[i]);
            node->add_connection(connection);
        }
    }

    TunnelNode* root = get_node_by_name(nodes, "AA");
    cout << root->get_subtree_max_rate(30) << endl;

    return 0;
}

int TunnelNode::get_subtree_max_rate(int timeout) {
    if (timeout <= 0) { // no time left
        return 0;
    } else { // some time left
        int this_flow = 0;
        if (this->flow_rate != 0 && find(this->opened.begin(), this->opened.end(), this->name) == this->opened.end()) {
            this->opened.push_back(this->name);
            --timeout; // one minute to activate node
            this_flow = this->flow_rate * timeout; // amount of flow this node can send
        }
        --timeout; // one minute to walk to next node
        int max = 0;
        for (int i = 0; i < connections.size(); i++) {
            // add this opened nodes to the list of the children opened nodes
            for (int j = 0; j < this->opened.size(); j++) {
                connections[i]->opened.push_back(this->opened[j]);
            }
            int rate = connections[i]->get_subtree_max_rate(timeout);
            if (rate > max) {
                max = rate;
            }
        }
        return max + this_flow;
    }
}

void TunnelNode::add_connection(TunnelNode* node) {
    connections.push_back(node);
}