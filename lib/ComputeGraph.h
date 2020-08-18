#ifndef COMPUTEGRAPH
#define COMPUTEGRAPH
#include "OpNode.h"

class ComputeGraph
{
    private:
        OpNode* target;
        int function_counter;
        int constant_counter;
        OpNode* forwardNode(OpNode* node);
        void backwardNode(OpNode *node);
        void cleandiffNode(OpNode *node);
        OpNode* createFunctionNode();
        OpNode* createConstantNode(float a);

    public:
        ComputeGraph();
        void    set(OpNode* a);
        void    forward(void);
        void    backward(void);
        OpNode* add(OpNode* a, OpNode* b);
        OpNode* add(OpNode* a, float b);
        OpNode* add(float a, float b);
        OpNode* mul(OpNode* a, OpNode* b);
        OpNode* mul(OpNode* a, float b);
        OpNode* mul(float a, float b);
        OpNode* pow(OpNode* a, OpNode* b);
        OpNode* pow(OpNode* a, float b);
        OpNode* pow(float a, float b);

};

#endif