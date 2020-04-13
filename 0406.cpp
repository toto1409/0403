#include<iostream>
#include<vector>
using namespace std;

class Input {
private:
	string data;
public:
	Input(string data) : data(data) {}
	Input(const Input& ip) {
		data = ip.getData();
	}
	string getData() const {
		return this->data;
	}
};
class State;
class Transition {
private:
	Input ip;
	State* to;
public:
	Transition(Input ip, State* to) : ip(ip), to(to) {}
	Input getInput() {
		return this->ip;
	}
	const State* getTransitionState() {
		return this->to;
	}
};

class State {
private:
	string label;
	bool isStart;
	bool isEnd;
	vector<Transition> transitions;
public:
	State(string label = "", bool isStart = false, bool isEnd = false) :
		label(label), isStart(isStart), isEnd(isEnd) {}
	State(const State& s) {
		this->label = s.getLabel();
	}
	string transit(Input ip) {
		for (vector<Transition>::iterator it = transitions.begin(); it < transitions.end(); ++it) {
			if ((*it).getInput().getData() == ip.getData())
				return (*it).getTransitionState()->getLabel();
		}
		return string("");
	}
	string getLabel() const {
		return this->label;
	}
	void addTransition(Transition t) {
		this->transitions.push_back(t);
	}
};

class StateMachine {
private:
	vector<State> states;
	int currentStateIndex;
	Input* currentInput;
	void consumeInput();
public:
	void addState();
	void acceptInput();
	void addTransition();
};

void StateMachine::addTransition() {
	string start, end;
	string inputLabel;
	cout << "Enter the start state of the transition \n";
	cin >> start;
	cout << "Enter the endstate of the transition \n";
	cin >> end;
	cout << "Enter the input label of the transition\n";
	cin >> inputLabel;
	vector<State>::iterator sit = states.end(), eit = states.end();
	for (vector<State>::iterator it = states.begin(); it < states.end(); ++it) {
		if ((*it).getLabel() == start) {
			sit = it;
		}
		if ((*it).getLabel() == end) {
			eit = it;
		}
		if (sit != states.end() && eit != states.end()) {
			break;
		}
	}
	if (sit == states.end() || eit == states.end()) {
		cout << "Both the states not present\n";
		return;
	}
	Transition t(Input(inputLabel), &(*eit));
	(*sit).addTransition(t);
}

void StateMachine::addState() {
	string stateLabel;
	cin >> stateLabel;
	for (vector<State>::iterator it = states.begin(); it < states.end(); ++it) {
		if ((*it).getLabel() == stateLabel) {
			cout << "a state with label " + stateLabel + " already present" << std::endl;
			return;
		}
	}
	char isStart, isEnd;
	cout << "Is a start state ? y/n" << std::endl;
	cin >> isStart;
	cout << "Is a end state ? y/n" << std::endl;
	cin >> isEnd;
	State s(stateLabel, isStart == 'y', isEnd == 'y');
	this->states.push_back(s);
	if (isStart == 'y') {
		this->currentStateIndex = states.size() - 1;
	}
}
void StateMachine::acceptInput() {
	string inputLabel;
	cin >> inputLabel;
	string nextStateLabel = this->states[this->currentStateIndex].transit(Input(inputLabel));
	vector<State>::iterator it = states.begin();
	for (; it < states.end(); ++it) {
		if ((*it).getLabel() == nextStateLabel) {
			this->currentStateIndex = it - states.begin();
			cout << "current state is " + nextStateLabel << std::endl;
			break;
		}
	}
	if (it == states.end())
		cout << "no transition for the input form currentState" << std::endl;
}


int main() {
	StateMachine sm;
	sm.addState();
	sm.addState();
	sm.addTransition();
	sm.addTransition();
	sm.addTransition();
	sm.addTransition();
	while (1) {
		sm.acceptInput();
	}
	return 0;
}