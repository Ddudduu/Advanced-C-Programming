#include <string>
#include <vector>
#include <iostream>
using namespace std;

void error(string s)

{
	throw runtime_error(s);
}

class Calculator

{
public:
	void calculate();
private:
	struct Variable;

	double get_value(string s);
	void set_value(string s, double d);
	bool is_declared(string s);
	double expression();
	double primary();
	double term();
	double declaration();
	double statement();
	void clean_up_mess();

	vector<Variable> names;

	const string prompt = "> ";
	const string result = "= ";


};
struct Token {
	char kind;
	double value;
	string name;
	Token(char ch) :kind(ch), value(0) { }
	Token(char ch, double val) :kind(ch), value(val) { }
	Token(char ch, string name) :kind(ch), name(name) {}
};

class Token_stream {
private:
	bool full;
	Token buffer;
public:
	Token_stream() :full(0), buffer(0) { }

	Token get();
	void putback(Token t) {
		if (full) error("putback() into a full buffer");
		buffer = t; full = true;
	}

	void ignore(char);
};

const char let = 'L';
const char quit = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';


Token Token_stream::get()
{
	if (full) {
		full = false;
		return buffer;
	}

	char ch;
	cin >> ch;

	switch (ch) {
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case ';':
	case '=':
		return Token(ch);
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	{
		cin.unget();
		double val;
		cin >> val;
		return Token(number, val);
	}
	default:
		if (isalpha(ch)) {
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
			cin.unget();
			if (s == "let") return Token(let);
			if (s == "quit") return Token(quit);
			return Token(name, s);
		}
		error("Bad token");
	}
}

void Token_stream::ignore(char c)
{
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch;
	while (cin >> ch)
		if (ch == c) return;
}

struct Calculator::Variable {
	string name;
	double value;
	Variable(string n, double v) :name(n), value(v) { }
};	

double Calculator::get_value(string s)
{
	names.push_back(Variable("e", 2.71828));
	names.push_back(Variable("pi", 3.14159));

	for (int i = 0; i < names.size(); ++i)
	{
		if (names[i].name == s) return names[i].value;
	}
	error("get: undefined name ");
}

void Calculator::set_value(string s, double d)
{
	for (int i = 0; i <= names.size(); ++i)
		if (names[i].name == s) {
			names[i].value = d;
			return;
		}
	error("set: undefined name ");
}

bool Calculator::is_declared(string s)
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return true;
	return false;
}

Token_stream ts;

double Calculator::primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{	double d = expression();
	t = ts.get();
	if (t.kind != ')') 
		error("'(' expected");
	return d;
	}
	case '-':
		return -primary();
	case'+':
		return primary();
	case'--':
		return primary();
	case '++':
		return primary();
	case number:
		return t.value;
	case name:
		return get_value(t.name);
	default:
		error("primary expected");
	}
}

double Calculator::term()
{
	double left = primary();
	Token t = ts.get(); 

	while (true) {
		switch (t.kind) {
		case '*':
			left *= primary();
			t = ts.get(); 
			break;

		case '/':
		{	
			double d = primary();
			if (d == 0) 
				error("divide by zero");
			left /= d;
			t = ts.get(); 
			break;
		}

		default:
			ts.putback(t);
			return left;
		}
	}
}

double Calculator::expression()
{
	double left = term();
	Token t = ts.get(); 

	while (true) {
		switch (t.kind) {
		case '+':
			left += term();
			t = ts.get();
			break;
		case '-':
			left -= term();
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}

double Calculator::declaration()
{
	Token t = ts.get();
	if (t.kind != name) 
		error("name expected in declaration");
	string name = t.name;

	if (is_declared(name))
		error("Declared twice");

	Token t2 = ts.get();

	if (t2.kind != '=')
		error("= missing in declaration of ");

	double d = expression();
	names.push_back(Variable(name, d));
	return d;
}

double Calculator::statement()
{
	Token t = ts.get();
	switch (t.kind) {
	case let:
		return declaration();
	default:
		ts.putback(t);
		return expression();
	}
}

void Calculator::clean_up_mess()
{
	ts.ignore(print);
}

const string prompt = "> ";
const string result = "= ";

void Calculator::calculate()
{
	while (true) try {
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t = ts.get();
		if (t.kind == quit) return;
		ts.putback(t);
		cout << result << statement() << endl;
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
		clean_up_mess();
	}
}

int main()
try {
	Calculator c;
	c.calculate();
	return 0;
}
catch (exception& e) {
	cerr << "exception: " << e.what() << endl;
	system("pause");
	return 1;
}
catch (...) {
	cerr << "exception\n";
	system("pause");
	return 2;
}