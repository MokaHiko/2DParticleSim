#include "ParticleSimulator.h"

ParticleSimulator* Simulator;
int main(int argc, char* argv[])
{
    Simulator = new ParticleSimulator();
    Simulator->Init();
    while (!Simulator->isClosed())
    {
        Simulator->HandleInput();
        Simulator->Update();
        Simulator->Render();
    }
    Simulator->Clean();
    delete Simulator;
    return 0;
}

