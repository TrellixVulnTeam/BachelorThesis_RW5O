#include "stdafx.h"

#include "CoolDownTester.h"

namespace plt = matplotlibcpp;

CoolDownTester::CoolDownTester() : number_steps(1000) {

    Energy energy;
    int* progress;
    this->sas.push_back(SimulatedAnnealing(number_steps, new Hajek(), energy, false));
    this->sas.push_back(SimulatedAnnealing(number_steps, new ExponentialCoolDown(), energy, false));
    this->sas.push_back(SimulatedAnnealing(number_steps, new Lineary(), energy, false));
    this->sas.push_back(SimulatedAnnealing(number_steps, new Inverse(), energy, false));
}

CoolDownTester::CoolDownTester(int number_steps) {

    int* progress;
    Energy energy;
    this->number_steps = number_steps;
    this->sas.push_back(SimulatedAnnealing(number_steps, new Hajek(), energy, false));
    this->sas.push_back(SimulatedAnnealing(number_steps, new ExponentialCoolDown(), energy, false));
    this->sas.push_back(SimulatedAnnealing(number_steps, new Lineary(), energy, false));
    this->sas.push_back(SimulatedAnnealing(number_steps, new Inverse(), energy, false));
}

void CoolDownTester::compareDifferentCoolDownSchedules() {
    
    int max_num_steps = 0;

    for (auto iter = sas.begin(); iter != sas.end(); ++iter) {
        
        int good_swaps = 0;
        iter->execute(dither_texture_path, good_swaps);

    }

    // Set the size of output image to 1200x780 pixels
    plt::figure_size(1200, 780);

    for (int i = 0; i < sas.size(); i++) {

        SimulatedAnnealing currentAnnealing = sas[i];
        Energy currentEnergy = currentAnnealing.getEnergy();
        std::vector<int> x(currentEnergy.size());
        for (int j = 0; j < currentEnergy.size(); j++) {
            x.at(j) = j;
        }
        if (currentAnnealing.getNumSwaps() > max_num_steps) max_num_steps = currentAnnealing.getNumSwaps();
        // Plot line from given x and y data. Color is selected automatically.
        std::stringstream legend_commentary;
        legend_commentary << currentAnnealing.getSchedule()->getName() << " " << currentAnnealing.getSchedule()->getFunction();
        plt::named_plot(legend_commentary.str(), x , currentEnergy);
    }
    //scaling x-axis
    plt::xlim(0, max_num_steps);
    // Add graph title
    std::stringstream ss;
    ss << "Energies compared to different cooldown funcions";
    plt::title(ss.str());
    // Enable legend.
    plt::legend();
    // Save the image (file format is determined by the extension)
    std::stringstream ss2;
    ss2 << this->folder_energy << "Energy_Cooldown_compared_steps_" << max_num_steps << ".png";
    plt::save(ss2.str());

}