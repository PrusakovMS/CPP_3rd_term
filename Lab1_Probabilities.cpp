#include <iostream>
#include <set>
#include <random>
#include <string>
#include <typeinfo>
#include <map>
#include <vector>

using namespace std;

class BaseState {
public:
    virtual bool contains(int s) const {
        return false;
    }

    virtual void type() const = 0;
};

class DiscreteState : public BaseState {
private:
    int const state;

public:
    DiscreteState(int state): state(state) { }

    bool contains(int s) const {
        return s == state;
    }

    void type() const {
        cout << "DiscreteState" << endl;
    }
};

class SegmentState : public BaseState {
private:
    int const beg, end;

public:
    SegmentState(): beg(0), end(-1) { }
    SegmentState(int beg, int end): beg(beg), end(end) { }

    bool contains(int s) const {
        return s >= beg && s <= end;
    }

    void type() const {
        cout << "SegmentState" << endl;
    }
};

class SetState : public BaseState {
private:
    set<int> const states;

public:
    SetState(): states() { }
    SetState(set<int> const &src): states(src) { }

    bool contains(int s) const {
        return states.count(s) > 0;
    }

    void type() const {
        cout << "SetState" << endl;
    }
};

class ProbabilityTest {
private:
    unsigned seed;
    int test_min, test_max;
    unsigned test_count;

public:
    ProbabilityTest(unsigned seed, int test_min, int test_max, unsigned test_count): seed(seed), test_min(test_min),test_max(test_max), test_count(test_count) { }

    float operator()(BaseState const &s) const {
        default_random_engine rng(seed);
        uniform_int_distribution<int> dstr(test_min,test_max);
        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_count; ++cnt)
            if (s.contains(dstr(rng))) ++good;


        return static_cast<float>(good)/static_cast<float>(test_count);
    }
};

BaseState* Init(string str) {
    BaseState *s;
    map<int, string> classes = {{1, "DiscreteState"}, {2, "SegmentState"}, {3, "SetState"}};
	    if (str == "DiscreteState") 
	{
        cout << "Enter state (one number)" << endl;
        int n;
        cin >> n;
        s = new DiscreteState(n);
    }
    if (str == "SegmentState") 
	{
        cout << "Enter state (begin number and end number)" << endl;
        int beg, end;
        cin >> beg >> end;
        s = new SegmentState(beg, end);
    }
    if (str == "SetState") 
	{
        cout << "Enter state (amount of states N and list of N states)" << endl;
        int n;
        cin >> n;
        set<int> st;
        for (int cnt = 0; cnt != n; ++cnt) {
            int state;
            cin >> state;
            st.insert(state);
        }
        s = new SetState(st);
    }
    return s;
}

int main(int argc, const char * argv[]) {
    int left, right;
    cout << "Enter left and right borders of states (0 and 100 for example)" <<endl;
    cin >> left >> right;

    //Base test is for tasks 1 and 2
    map<int, string> classes = {{1, "DiscreteState"}, {2, "SegmentState"}, {3, "SetState"}};
    cout << "Which type: 1.Discrete state, 2.Segment state, 3.Setstate" <<endl;
    int scn;
    cin >> scn;
    BaseState &state = *Init(classes[scn]);
    vector<float> y1; //Probability
    vector<int> x; //Test count
    cout << "Enter maximum amount of tests" << endl;
    int max_x;
    cin >> max_x;
    for (int cnt = 0; cnt != max_x + 1; ++cnt) {
        ProbabilityTest test(10, left, right, cnt);
        y1.push_back(test(state));
        x.push_back(cnt);
    }
	for (unsigned int i = 0; i < y1.size(); i++) 
	{
	cout << y[i] << " "; 
	}
	cout<<endl;
	for (unsigned int i = 0; i < x.size(); i++) 
	{
	cout << x[i] << " "; 
	}	
    return 0;
}
