# dlist-applications
##  Summary

RPN reverse-Polish notation calculator and a call center simulation program implemented by self-designed double linked lists.

## Motivation

The dlist-applications mainly focus on applying dynamic memory management, implementing a template container class (the double‐ended, doubly‐linked list, or Dlist), and using the at-most‐once invariant and existence, ownership, and conservation rules to implement two simple applications using this structure.

## Structure

The dlist-applications include a templated double-ended, doubly-linked list, or `dlist.h`, and two applications built with `dlist.h`: a reverse-Polish notation calculator and a call center simulation program.

## Details

#### The Double-Ended, Doubly-Linked List

The double‐ended, doubly-linked list, or Dlist, is a templated container. It supports the following operational methods:

> isEmpty: a predicate that returns true if the list is empty, false otherwise.
>
> insertFront/insertBack: insert an object at the front/back of the list, respectively.
>
> removeFront/removeBack: remove an object from the front/back of a non-empty list, respectively; throws an exception if the list is empty.

This list is templated across the contained type, T, it is a container of pointers-to-T, not container of instances of T.

A detailed version of functions in the `dlist.h` is

```c++
template <class T>
class Dlist
{
	// OVERVIEW: contains a double-ended, doubly-linked list of // objects

	public:
	// Operational methods
	bool isEmpty() const;
	// EFFECTS: returns true if list is empty, false otherwise
	void insertFront(T *op);
	// MODIFIES: this
	// EFFECTS: inserts op at the front of the list
	void insertBack(T *op);
	// MODIFIES: this
	// EFFECTS: inserts op at the back of the list
	T *removeFront();
	// MODIFIES: this
	// EFFECTS: removes and returns first object from non-empty list
	// throws an instance of emptyList if empty
	T *removeBack();
	// MODIFIES: this
	// EFFECTS: removes and returns last object from non-empty list
	// throws an instance of emptyList if empty
	// Maintenance methods

	Dlist(); // constructor
	Dlist(const Dlist &l); // copy constructor
	Dlist &operator=(const Dlist &l); // assignment operator
	~Dlist(); // destructor
  
	private:
	// A private type
	struct node
	{
	node *next;
	node *prev;
	T *op;
	};
	node *first; // The pointer to the first node (NULL if none)
  	node *last; // The pointer to the last node (NULL if none)

  	// Utility methods
	void removeAll();
	// EFFECTS: called by destructor/operator= to remove and destroy
	// all list elements
	void copyAll(const Dlist &l);
	// EFFECTS: called by copy constructor/operator= to copy elements
	// from a source instance l to this instance
};
  
```

The `dlist.h` is implemented in `dlist.cpp`.

#### Reverse-Polish Notation Calculator

The first application demo is the simple reverse‐Polish notation (RPN) calculator operating on complex integers (one in which the operators appear after their respective operands, rather than between them). For example, `(2 + 3) * 5` would be computed in RPN Calculator as `2 3 + 5 *`.

It takes its input from the standard input stream `std::cin`, and writes its output to the standard output stream `std::cout`. The stack only contains complex integers.A complex integer

The following table gives the commands of the calculator (all the arithmetic operations are on complex numbers).

| Operation Name    | Detailed Instructions                    |
| ----------------- | ---------------------------------------- |
| A complex integer | A complex integer has the form as 𝑚+𝑛𝑖, 𝑚−𝑛𝑖, −𝑚+𝑛𝑖, or −𝑚−𝑛𝑖, where both 𝑚 and 𝑛 are non-negative integers composed of digits [$0-9$] and cannot be omitted. You can also assume that there are no spaces in any input complex integer, no matter it is valid or invalid (for invalid case, you need to report an error; see below for details). A complex integer, when entered, is pushed onto the stack. You can assume the real part and the imaginary part of the input complex numbers and the intermediate results are within the range [$−2^{31}$,$2^{31}−1$]. |
| +                 | Pop the top two numbers off the stack, add numbers together, and push the result onto the top of the stack. This requires a stack with at least two operands. |
| ‐                 | Pop the top two numbers off the stack. Assume that the first popped number is a and the second is b. Then, subtract the first number a from the second b (i.e., calculate b − a), and push the result onto the top of the stack. This requires a stack with at least two operands. |
| *                 | Pop the top two numbers off the stack, multiply them together, and push the result onto the top of the stack. This requires a stack with at least two operands. |
| n                 | Negate: pop the top item off the stack, multiply it by ‐1, and push the result onto the top of the stack. This requires a stack with at least one operand. |
| d                 | Duplicate: pop the top item off the stack and push two copies of the number onto the top of the stack. This requires a stack with at least one operand. |
| r                 | Reverse: pop the top two items off the stack, push the first popped item onto the top of the stack and then push the second item onto the top of the stack. This just reverses the order of the top two items on the stack. This requires a stack with at least two operands. |
| p                 | Print: print the top item on the stack to the standard output, followed by a newline. This requires a stack with at least one operand and leaves the stack unchanged. When you print a complex integer, it should have the form as 𝑚+𝑛𝑖, 𝑚−𝑛𝑖, −𝑚+𝑛𝑖, or −𝑚−𝑛𝑖, where both 𝑚 and 𝑛 are non-negative integers composed of digits [$0-9$] and cannot be omitted. There are no spaces in the output of a complex integer. In the special case where 𝑚=0, the output should be either 0+𝑛𝑖 or 0−𝑛𝑖, where 𝑛≥0. In the special case where 𝑛=0, the output should be either 𝑚+0𝑖 or −𝑚+0𝑖, where 𝑚≥0. |
| c                 | Clear: pop all items from the stack. This input is always valid. |
| a                 | Print‐all: print all items on the stack in one line, from top‐most to bottom‐most, each followed by a single space. Please refer to the explanation for the “p” command on the output format of each complex integer. The end of the output must be followed by a newline. This input is always valid and leaves the stack unchanged. If the stack is empty, this operation will print an empty line. |
| q                 | Quit: exit the calculator. This input is always valid. |

Possible error cases are `Bad input` or `Not enough operands`. A sample output is

```tcl
3+1i
4+2i
+
*
Not enough operands
5+3i
a
5+3i 7+3i
p
5+3i
q
```

The RPN calculator is implemented in `calc.cpp`.

#### Call Center Simulation

The second application is a simple discrete‐event simulator, modeling the behavior of a single reservation agent at *Delta Airlines*. When a customer calls *Delta*, s/he is asked to enter his/her membership number. Calls are then answered in priority order: customers who are *Platinum Elite* (those having flown 75,000 miles or more in the current or previous calendar year) have their calls answered first, followed by *Gold Elite* (50,000), *Silver Elite* (25,000), and finally "regular" customers.

We call this a discrete‐event simulator because it considers time as a discrete sequence of points, with zero or more events happening at each point in time. In our simulator, time starts at "time 0", and progresses in increments of one. Each increment is referred to as a "tick".

A discrete‐event simulator is usually driven by a script of "independent events" plus a set of "causal rules".
In our simulator, the independent events are the set of customers that place calls to the call center. These events are in a file. The first line of the file has a single entry which is the number of events (N) contained in the next N lines. Each of those N lines has the following format:
`<timestamp> <name> <status> <waiting> <duration>`

Each field is delimited by one or more whitespace characters. You may assume that the lines are sorted in timestamp‐order, from lowest to highest. Timestamps need not be unique.

| Format      | Instruction                              |
| ----------- | ---------------------------------------- |
| <timestamp> | an integer, zero or greater, denoting the tick at which this call comes in. |
| <name>      | a string, which is the name of the caller and has no spaces. |
| <status>    | one of the following four strings: "regular" – regular status, "silver" – silver elite, "gold” – gold elite, "platinum" – platinum elite |
| <waiting>   | a positive integer, denoting the number of ticks the caller will wait to be served. |
| <duration>  | a positive integer, denoting the number of ticks required to service this call. |

In summary, there may be four events occurring at a timestamp 𝑡, which are the agent finishing serving a call, a caller hanging up, a caller entering into the queue, and the agent beginning to serve a new call. Their occurring time can be thought as: the agent finishes serving a call at time 𝑡−𝜖, a caller hangs up at time 𝑡, a caller enters into the queue at time 𝑡+𝜖, and the agent begins to serve a new call at time 𝑡+2𝜖, where 𝜖 is a very small positive number. 

A sample input and output would be

```
// sample input
3
0 Andrew gold 2 2
0 Chris regular 1 1
1 Brian silver 2 1

// sample output
Starting tick #0
Call from Andrew a gold member
Call from Chris a regular member
Answering call from Andrew
Starting tick #1
Chris hangs up
Call from Brian a silver member
Starting tick #2
Answering call from Brian
Starting tick #3
```

The RPN calculator is implemented in `call.cpp`.

## Usage

1. Having all the files prepared as `dlist.h`, `dlist.cpp`, `calc.cpp` and `call.cpp`.

2. Compile the program with the following command.

   `g++ -g –Wall –o calc calc.cpp   // the RPN calculator    ` 

   `g++ -g –Wall –o call call.cpp   // the call center simulation`

3. Test the program with the following command.

   `./calc`

   `./call < sample > test.out`