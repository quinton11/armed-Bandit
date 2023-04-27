#include "agent.h"

Agent::Agent() {}
Agent::Agent(std::string mName, AgentMode aMode, GameMode gMode)
    : modelName(mName), agentMode(aMode), gameMode(gMode) {}

void Agent::setAgent(AgentMode am, GameMode gm)
{
    agentMode = am;
    gameMode = gm;
}

void Agent::resetActionValues()
{
    actionValues.clear();
    actionSteps.clear();

    //
    // actionValues.insert(actionValues.end(), {{Action::One, 0.0}});
    actionValues = {
        {Action::One, 0},
        {Action::Two, 0},
        {Action::Three, 0},
        {Action::Four, 0},
        {Action::Five, 0},
        {Action::Six, 0}};

    actionSteps = {
        {Action::One, 0},
        {Action::Two, 0},
        {Action::Three, 0},
        {Action::Four, 0},
        {Action::Five, 0},
        {Action::Six, 0}};
}
void Agent::setActions()
{
    actions.clear();
    actions.insert(actions.end(), {
                                      Action::One,
                                      Action::Two,
                                      Action::Three,
                                      Action::Four,
                                      Action::Five,
                                      Action::Six,
                                  });
}

void Agent::printWeight()
{
    for (std::map<Action, float>::iterator av = actionValues.begin(); av != actionValues.end(); av++)
    {
        if (av->first == Action::One)
        {
            std::cout << "Action one: " << av->second << std::endl;
        }
        else if (av->first == Action::Two)
        {
            std::cout << "Action two: " << av->second << std::endl;
        }
        else if (av->first == Action::Three)
        {
            std::cout << "Action three: " << av->second << std::endl;
        }
        else if (av->first == Action::Four)
        {
            std::cout << "Action four: " << av->second << std::endl;
        }
        else if (av->first == Action::Five)
        {
            std::cout << "Action five: " << av->second << std::endl;
        }
        else if (av->first == Action::Six)
        {
            std::cout << "Action six: " << av->second << std::endl;
        }
    }
}

void Agent::updateWeights(float reward, int steps)
{
    updateActionValue(reward, steps);
}

void Agent::updateActionValue(float reward, int steps)
{
    // update action timestep
    actionSteps[selectedAction] += 1;

    int ts = actionSteps[selectedAction];
    float prevR = actionValues[selectedAction];

    std::cout << "Action has been selected x" << ts << std::endl;

    // calculate new estimate for action
    float updated = estimate(reward, prevR, steps);

    // update
    actionValues[selectedAction] = updated;
}

float Agent::estimate(float r, float prevV, float ts)
{
    // action value estimate
    std::cout << "Calculating update..." << std::endl;
    std::cout << "Prev value: " << prevV << std::endl;
    std::cout << "Step fraction: " << 1 / ts << std::endl;
    float update = prevV + (1.f / ts) * (r - prevV);
    std::cout << "Updated value: " << update << std::endl;

    return update;
}

bool Agent::takeAction(const Uint8 *state)
{

    SDL_PumpEvents();

    if (state[SDL_SCANCODE_A])
    {
        std::cout << "A" << std::endl;
        selectedAction = Action::One;
        // action 1
        return true;
    }
    else if (state[SDL_SCANCODE_S])
    {
        std::cout << "S" << std::endl;
        // action 2
        selectedAction = Action::Two;
        return true;
    }
    else if (state[SDL_SCANCODE_D])
    {
        std::cout << "D" << std::endl;
        // action 3
        selectedAction = Action::Three;
        return true;
    }
    else if (state[SDL_SCANCODE_F])
    {
        std::cout << "F" << std::endl;
        // action 4
        selectedAction = Action::Four;
        return true;
    }
    else if (state[SDL_SCANCODE_G])
    {
        std::cout << "G" << std::endl;
        // action 5
        selectedAction = Action::Five;
        return true;
    }
    else if (state[SDL_SCANCODE_H])
    {
        std::cout << "H" << std::endl;
        // action 6
        selectedAction = Action::Six;
        return true;
    }
    return false;
}
