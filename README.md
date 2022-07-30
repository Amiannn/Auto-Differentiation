# Auto-Differentiation
## Main Usage
```c
#include <iostream>
#include <cstdlib>
#include "lib\ComputeGraph.h"

using namespace std;

int main()
{
    ComputeGraph graph;
    OpNode *x = new OpNode("x1");  

    // cost(x) = 3*x^2 + 4*x + 5
    OpNode* cost = graph.add(graph.add(graph.mul(graph.pow(x, 2), 3), graph.mul(x, 4)), 5);
    
    // compute graph target on cost function
    graph.set(cost);

    // random set x value
    x->Set(rand());

    float learning_rate = 0.01;

    // gradient descent
    for(int i = 0;i < 500; i++)
    {
        // auto differentiation backward mode
        graph.backward();
        
        x->Set(x->Get() - learning_rate * x->diff);
    }

    // auto differentiation forward mode
    graph.forward();
 
    cout << "minimum value: " << cost->Get() << endl;

    system("pause");
    return 0;
}
```
