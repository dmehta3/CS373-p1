#include <bits/stdc++.h>
using namespace std;

class state;    //forward declaration
class transition{
    public:  
        state* from;
        char symbol;
        state* to;      
        transition(state* from, char symbol, state* to) //constructor
        {
            this->to = to;
            this->from = from;
            this->symbol = symbol;
        }
};
class state {
    public:
        vector<transition*> transitions;
        int id;
        bool start;
        bool accept;
        state(int id, bool start, bool accept) //constructor
        {
            this->id = id;
            this->start = start;
            this->accept = accept;
        }
};
void duplicate(vector<int> &v)        //remove duplicates from vector
{
    unordered_set<int> temp;
    auto final = remove_if(v.begin(), v.end(), [&temp](int const &i) {
        return !temp.insert(i).second;
    });
    v.erase(final, v.end());
};
int main(int argc, char* argv[]) {
    ifstream in(argv[1]);
    vector<transition*> Transitions;    //main list of transitions which will be used to make transition vectors for each state
    vector<state*> States;  //main list of all the states
    string line;    //each line from the input file
    while (getline(in, line)) {
        istringstream iss(line);
        string firstWord;
        iss >> firstWord;
        if (firstWord == "state") {     //create an accept, start, or (accept and start) state
            int num;
            string specialty;
            string specialty2;  //will be used if accept and start
            iss >> num >> specialty >> specialty2;
            if (specialty2 == "start" || specialty2 == "accept") {
                state* s = new state(num, true, true);
                States.push_back(s);
            }
            else if (specialty == "start") {
                state* s = new state(num, true, false);
                States.push_back(s);
            }
            else {
                state* s = new state(num, false, true);
                States.push_back(s);
            }
        }
        else {  //transition line
            int p;
            char x;
            int q;
            iss >> p >> x >> q;
            bool p_flag = false;
            bool q_flag = false;
            for (state* s : States) {   //check if either p or q is already existing
                if (s->id == p) {
                    p_flag = true;        
                }
                if (s->id == q) {
                    q_flag = true;
                }
            }
            if(!p_flag) {       //doesn't exist? create a state 
                state* s = new state(p, false, false);
                States.push_back(s);
            }
            if(!q_flag && (p != q)) {
                state* s = new state(q, false, false);
                States.push_back(s);
            }
            state* pstate;
            state* qstate;
            for (state* s : States) {   //assign pointers to p and q
                if (s->id == p) {
                    pstate = s;     
                }
                if (s->id == q) {
                    qstate = s;
                }
            }
            transition* t = new transition(pstate, x, qstate);  //create a transition
            Transitions.push_back(t);
        }
    }
    in.close();
    state* start;
    vector<state*> accept;
    for (state* s : States) {   //for each state, loop through all transitions and add them to the state transitions if p matches and find the start state
        for (transition* t : Transitions) {
            if (t->from->id == s->id) {
                s->transitions.push_back(t);
            }
        }
        if (s->start == true) {
            start = s;
        }
        if(s->accept == true) {
            accept.push_back(s);
        }
    }
    string input = argv[2];
    vector<int> configurations;
    configurations.push_back(start->id); //put the start state into the configurations
    int i = 0;
    while (i < input.length()) {    //start iterating through the string
        char c = input[i]; 
        int limit = configurations.size();  //set a limit for the loop outside of the loop
        for (int j = 0; j < limit; ++j) {
            if (configurations[j] != -1) {  //check if the configuration is valid
                int curr = configurations[j];   //set a current state
                state* temp;    //pointer to current state
                for (state* s : States) {
                    if (s->id == curr) {
                        temp = s;
                    }
                }
                bool working = false;   //assume their are no valid pathways
                for (transition* t : temp->transitions) {   //loop through the state's transitions
                    if (t->symbol == c && working == false) {   //if a symbol matches, add it to configurations
                        configurations[j] = t->to->id;
                        working = true; //this sets working to true, allowing additional configurations to be added to the vector
                        continue;   //go to the next iteration to prevent a duplicate
                    }
                    if (t->symbol == c && working == true) {
                        configurations.push_back(t->to->id);    //any additional pathways will be added
                    }
                }
                if (working == false) { //their were no valid pathways, the configuration is dead
                    configurations[j] = -1;
                }
            }
        }
        i++;    //iterate while loop
    }
    // cout << configurations.size() << endl;
    vector<int> print;
    bool y = false;
    for (int i = 0; i < configurations.size(); i++) {
        for (int j = 0; j < accept.size(); j++) {
            if (configurations[i] == accept[j]->id && y == false) {
                cout << "accept ";
                print.push_back(configurations[i]);
                y = true;
                continue;
            }
            if (configurations[i] == accept[j]->id && y == true) {
                print.push_back(configurations[i]);
            }
        }
    }
    if (y == false) {
        cout << "reject ";
        for (int i = 0; i < configurations.size(); i++) {
            print.push_back(configurations[i]);
        }
    }
    duplicate(print);
    for (int i = 0; i < (print.size() - 1); i++) {
        cout << print[i] << " ";
    }
    cout << print[print.size() - 1] << endl;
}