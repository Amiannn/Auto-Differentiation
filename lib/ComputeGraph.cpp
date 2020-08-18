#include "ComputeGraph.h"

ComputeGraph::ComputeGraph()
{
    this->target = NULL;
    this->function_counter = 0;
    this->constant_counter = 0;
}

OpNode* ComputeGraph::createFunctionNode()
{
    OpNode* node = new OpNode("F" + std::to_string(this->function_counter));
    this->function_counter++;
    return node;
}

OpNode* ComputeGraph::createConstantNode(float a)
{
    OpNode* node = new OpNode("C" + std::to_string(this->constant_counter));
    node->Set(a);
    this->constant_counter++;
    return node;
}

void ComputeGraph::set(OpNode* a)
{
    this->target = a;
}

OpNode* ComputeGraph::forwardNode(OpNode* node)
{
    OpNode* a;
    OpNode* b;

    if(node->GetMode())
    {
        a = this->forwardNode(node->a);
        b = this->forwardNode(node->b);
        node->ALU(a, b, node->GetMode());
    }
    node->Show();
    return node;
}

void ComputeGraph::forward(void)
{
    this->forwardNode(this->target);
}

void ComputeGraph::cleandiffNode(OpNode* node)
{
    if(node == NULL) return;
    node->diff = 0.0;
    this->cleandiffNode(node->a);
    this->cleandiffNode(node->b);
}

void ComputeGraph::backwardNode(OpNode* node)
{
    if(node->GetMode())
    {
        node->dif();
        this->backwardNode(node->a);
        this->backwardNode(node->b);        
    }
}

void ComputeGraph::backward(void)
{
    this->cleandiffNode(this->target);
    this->target->diff = 1.0;
    this->backwardNode(this->target);
}

OpNode* ComputeGraph::add(OpNode* a, OpNode* b)
{
    OpNode* node = this->createFunctionNode();
    node->ALU(a, b, 1);
    return node;
}

OpNode* ComputeGraph::add(OpNode* a, float b)
{
    OpNode* node = this->createFunctionNode();
    OpNode* B = this->createConstantNode(b);

    node->ALU(a, B, 1);
    return node;
}

OpNode* ComputeGraph::add(float a, float b)
{
    OpNode* node = this->createFunctionNode();
    OpNode* A = this->createConstantNode(a);
    OpNode* B = this->createConstantNode(b);

    node->ALU(A, B, 1);
    return node;
}

OpNode* ComputeGraph::mul(OpNode* a, OpNode* b)
{
    OpNode* node = this->createFunctionNode();
    
    node->ALU(a, b, 2);
    return node;
}

OpNode* ComputeGraph::mul(OpNode* a, float b)
{
    OpNode* node = this->createFunctionNode();
    OpNode* B = this->createConstantNode(b);
    
    node->ALU(a, B, 2);
    return node;
}

OpNode* ComputeGraph::mul(float a, float b)
{
    OpNode* node = this->createFunctionNode();
    OpNode* A = this->createConstantNode(a);
    OpNode* B = this->createConstantNode(b);
    
    node->ALU(A, B, 2);
    return node;
}

OpNode* ComputeGraph::pow(OpNode* a, OpNode* b)
{
    OpNode* node = this->createFunctionNode();

    node->ALU(a, b, 3);
    return node;
}

OpNode* ComputeGraph::pow(OpNode* a, float b)
{
    OpNode* node = this->createFunctionNode();
    OpNode* B = this->createConstantNode(b);

    node->ALU(a, B, 3);
    return node;
}

OpNode* ComputeGraph::pow(float a, float b)
{
    OpNode* node = this->createFunctionNode();
    OpNode* A = this->createConstantNode(a);
    OpNode* B = this->createConstantNode(b);

    node->ALU(A, B, 3);
    return node;
}