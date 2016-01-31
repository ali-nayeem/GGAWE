// standard includes
#include <iostream>
#include <string.h>

// the general include for eo
#include <eo>
#include "eoGAWE.h"

using namespace std;

#include "routeSet.h"
#include "inputData.h"
#include "popInit.h"
#include "routeFitness.h"
#include "routeSetEvalFunc.h"
#include "routeSetQuadCrossover.h"
#include "routeSetMutation.h"
#include "adjustedEvalFunc.h"

typedef eoMinimizingFitness MyFitT;
typedef RouteSet<double> Indi;
double penalizability(int a, int b);


ofstream fout("best.txt");
double avg[5];


//rng.reseed(time(0));

////fitness evaluators
//eoEvalFuncPtr< Route<double> > routeEval(routeFitness);
//RouteSetEvalFunc<Indi> routeSetEval;
//AdjustedEvalFunc<Indi> adjustedEval(routeSetEval);

////population
//eoPop<Indi> pop;
// popInit(pop, parameters["popSize"], parameters["routeSetSize"], routeSetEval);

////selection
//eoDetTournamentSelect<Indi> selectOne(parameters["tFit"]);
//double perc = (parameters["popSize"] - parameters["eilte"]) / parameters["popSize"]; //eilte
//eoSelectPerc<Indi> select(selectOne, perc);
//
////crossover
//RouteSetQuadCrossover<Indi> xover(parameters["pSwap"]);
//
////mutations
//BigMutation<Indi> bM(routeEval);
//SmallMutation<Indi> sM(parameters["pDelete"], routeEval);
//eoPropCombinedMonOp<Indi> mutation(sM, parameters["pSm"]);
//mutation.add(bM, 1 - parameters["pSm"]);

//stop after maxGen generations
//eoGenContinue<Indi> continuator(parameters["maxGen"]);
//CHECKPOINT
//eoCheckPoint<Indi> checkpoint(continuator);
// Create a counter parameter
//eoValueParam<unsigned> generationCounter(0, "Generation");
// Create an incrementor (sub-class of eoUpdater). Note that the
// parameter's value is passed by reference,
// so every time the incrementer is updated (every generation),
// the data in generationCounter will change.
//eoIncrementor<unsigned> increment(generationCounter.value());
// Add it to the checkpoint,
// so the counter is updated (here, incremented) every generation
//checkpoint.add(increment);

// now some statistics on the population:
// Best fitness in population
// eoBestFitnessStat<Indi> bestStat;
// Second moment stats: average and stdev
// eoSecondMomentStats<Indi> SecondStat;

// Add them to the checkpoint to get them called at the appropriate time
// checkpoint.add(bestStat);
// checkpoint.add(SecondStat);

//// The Stdout monitor will print parameters to the screen ...
//eoStdoutMonitor monitor(false);

// when called by the checkpoint (i.e. at every generation)
// checkpoint.add(monitor);

// the monitor will output a series of parameters: add them
//monitor.add(generationCounter);
//monitor.add(bestStat);
//monitor.add(SecondStat);

// A file monitor: will print parameters to ... a File, yes, you got it!
//eoFileMonitor fileMonitor("stats.txt", " ");

// the checkpoint mechanism can handle multiple monitors
// checkpoint.add(fileMonitor);

// the fileMonitor can monitor parameters, too, but you must tell it!
// fileMonitor.add(generationCounter);
//  fileMonitor.add(bestStat);
//  fileMonitor.add(SecondStat);

////THE ALGORITHM
//eoGAWE<Indi> gga(select, xover, mutation,
//                 adjustedEval, checkpoint, parameters["elite"]);

//    gga.best = pop[0];
//    gga.actualBest = pop[0]; 
//    cout << "Initial : " << gga.best.fitness() << endl << gga.best.D[0] << endl << gga.best.D[1] << endl << gga.best.D[2] << endl << gga.best.Dun << endl << gga.best.ATT<<endl;
// Apply algo to pop - that's it!
//gga(pop);

//output
//cout << "FINAL Population size\n" << pop.size() << endl;
//cout << "Best : " << gga.best << endl << gga.best.D[0] << endl << gga.best.D[1] << endl << gga.best.D[2] << endl << gga.best.Dun << endl << gga.best.ATT;
//
//fout << "Best : " << gga.best << endl << gga.best.D[0] << endl << gga.best.D[1] << endl << gga.best.D[2] << endl << gga.best.Dun << endl << gga.best.ATT << endl;
//avg += gga.best.D[0];

//  pop.sort();

void main_function(int argc, char **argv)
{
    rng.reseed(time(0));

    //fitness evaluators
    eoEvalFuncPtr< Route<double> > routeEval(routeFitness);
    RouteSetEvalFunc<Indi> routeSetEval;
    AdjustedEvalFunc<Indi> adjustedEval(routeSetEval);

    //population
    eoPop<Indi> pop;
    popInit(pop, parameters["popSize"], parameters["routeSetSize"], adjustedEval); //changed

    //selection
    eoDetTournamentSelect<Indi> selectOne(parameters["tFit"]);
    double perc = (parameters["popSize"] - parameters["eilte"]) / parameters["popSize"]; //eilte
    eoSelectPerc<Indi> select(selectOne, perc);

    //crossover
    RouteSetQuadCrossover<Indi> xover(parameters["pSwap"]);

    //mutations
    BigMutation<Indi> bM(routeEval);
    SmallMutation<Indi> sM(parameters["pDelete"], routeEval);
    eoPropCombinedMonOp<Indi> mutation(sM, parameters["pSm"]);
    mutation.add(bM, 1 - parameters["pSm"]);

    //stop after maxGen generations
    eoGenContinue<Indi> continuator(parameters["maxGen"]);
    //CHECKPOINT
    eoCheckPoint<Indi> checkpoint(continuator);
    // Create a counter parameter
    eoValueParam<unsigned> generationCounter(0, "Generation");
    // Create an incrementor (sub-class of eoUpdater). Note that the
    // parameter's value is passed by reference,
    // so every time the incrementer is updated (every generation),
    // the data in generationCounter will change.
    eoIncrementor<unsigned> increment(generationCounter.value());
    // Add it to the checkpoint,
    // so the counter is updated (here, incremented) every generation
    checkpoint.add(increment);
    // The Stdout monitor will print parameters to the screen ...
    eoStdoutMonitor monitor(false);

    // when called by the checkpoint (i.e. at every generation)
    checkpoint.add(monitor);

    // the monitor will output a series of parameters: add them
    monitor.add(generationCounter);
    //THE ALGORITHM
    eoGAWE<Indi> gga(select, xover, mutation,
                     adjustedEval, checkpoint, parameters["elite"]); //changed
    // cout << pop[0];
    gga.best = pop[0];
    gga.actualBest = pop[0];
    gga.initial = pop[0];
    gga.stableCount = parameters["stableCount"];
    cout << "Initial : " << gga.best.fitness() << endl << gga.best.D[0] << endl << gga.best.D[1] << endl << gga.best.D[2] << endl << gga.best.Dun << endl << gga.best.ATT << endl;
    for (int i = 0; i < parameters["maxIter"]; i++)
    {
        cout << endl << "-----------------------------------------" << endl << "Iteration:" << i << " started" << endl << endl;

        gga.genCount = parameters["maxGen"];
        gga(pop);

        vector< Route<double> > & routeSet = gga.best.mutableRs();
        double maxPenalizibility = -1;
        double minPenalizibility = INFINITY;
        bool visitedEdge[VERTICES_NO][VERTICES_NO];
        memset(visitedEdge, 0, VERTICES_NO * VERTICES_NO * sizeof (bool));
        vector<edge> edgeList;
        for (int r = 0; r < routeSet.size(); r++)
        {
            list<int>::const_iterator next = routeSet[r].R().begin();
            list<int>::const_iterator it = next++;
            for (; next != routeSet[r].R().end(); it++, next++)
            {
                int i = *it;
                int j = *next;
                if (visitedEdge[i][j] || visitedEdge[j][i])
                {
                    continue;
                }
                //else
                visitedEdge[i][j] = visitedEdge[j][i] = 1;
                double penalty = penalizability(i, j);
                if (penalty > maxPenalizibility)
                {
                    maxPenalizibility = penalty;
                }
                if (penalty < minPenalizibility)
                {
                    minPenalizibility = penalty;
                }
                edgeList.push_back(edge(i, j, penalty));
            }
        }
        //double randomPenalty = rng.uniform(minPenalizibility,maxPenalizibility);
        for (int i = 0; i < edgeList.size(); i++)
        {
            if ( (edgeList[i].penalizibility-minPenalizibility)/(maxPenalizibility-minPenalizibility) > 0.8)
            {
                int a = edgeList[i].a, b = edgeList[i].b;
                p[a][b]++;
                p[b][a]++;
            }
        }
        for (int i = 0; i < pop.size(); i++)
        {
            pop[i].invalidate();
            adjustedEval(pop[i]);
        }
        for (int i = 0; i < VERTICES_NO; i++)
        {
            for (int j = i + 1; j < VERTICES_NO; j++)
            {
                p[j][i] = p[i][j] = (1-parameters["e"])*p[i][j];
            }
        }
    }
    cout << "FINAL Population size\n" << pop.size() << endl;
    cout << "Best : " << gga.actualBest << endl << gga.actualBest.D[0] << endl << gga.actualBest.D[1] << endl << gga.actualBest.D[2] << endl << gga.actualBest.Dun << endl << gga.actualBest.ATT << endl;

    fout << "Best : " << gga.actualBest << endl << gga.actualBest.D[0] << endl << gga.actualBest.D[1] << endl << gga.actualBest.D[2] << endl << gga.actualBest.Dun << endl << gga.actualBest.ATT << endl;
    avg[0] += gga.actualBest.D[0];
    avg[1] += gga.actualBest.D[1];
    avg[2] += gga.actualBest.D[2];
    avg[3] += gga.actualBest.Dun;
    avg[4] += gga.actualBest.ATT;

}

int main(int argc, char** argv)
{
    gatherAllInfo();
    //    createInitialSolution();
    //    exit(0);

    for (int j = 0; j < parameters["run"]; j++)
    {
        fout << "Run:" << (j + 1) << endl;
        try
        {
            main_function(argc, argv);
        }
        catch (exception& e)
        {
            cout << "Exception: " << e.what() << '\n';
        }

        fout << "Current Avg D0:" << avg[0] / (j + 1);
        fout << "\n\n" << endl;
    }
    fout << "Avg D0:" << avg[0] / parameters["run"] << endl << "Avg D1:" << avg[1] / parameters["run"] << endl << "Avg D2:" << avg[2] / parameters["run"] << endl << "Avg Dun:" << avg[3] / parameters["run"] << endl << "Avg ATT:" << avg[4] / parameters["run"] << endl;
    fout.close();
    return (EXIT_SUCCESS);
}

double penalizability(int a, int b)
{
    return 1.0 * tr[a][b] / ((1 + p[a][b]) * (1 + d[a][b])); //* tr[a][b]
}