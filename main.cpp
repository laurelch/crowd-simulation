#include <QApplication>
#include "view.h"
#include "MIGBasicSim.h"
#include "Person.h"
//int main(int argc, char *argv[])
//{
//    QApplication a(argc,argv);
//    View w;
//    w.setCrowdCount(20);
//    float status[6]={0,0,0,0,1,0};
//    w.setParticle(19,status);
//    float status2[6]={3,3,0,0,0,1};
//    w.setParticle(0,status2);
//    w.show();
//    return a.exec();
//}

int main(int argc, char *argv[])
{
    QApplication a(argc,argv);
    View w;
    w.setCrowdCount(20);
    float status[6]={0,0,0,0,1,0};
    w.setParticle(19,status);
    float status2[6]={3,3,0,0,0,1};
    w.setParticle(0,status2);
    w.show();
    //return a.exec();

    //create output directory
    string outputDir = ".\\output";
    CreateDirectoryA(outputDir.c_str(),NULL);
    MIGBasicSim sim;
    //one person is infected, people[42].disease = 1.0;
    sim.setInfection(42,1.0);
    int num_steps = ceil(total_time / dt);
    int test_steps = 1;
    //main loop
    int img_count = 1;
    for (int i = 0; i < test_steps; ++i) {
        if (i % 100 == 0) {
            cout<<"main::outputCSV at step "<<i<<endl;
            sim.outputCSV(img_count);
        }
        sim.update();
    }

    cout << "Done." << endl;

    return a.exec();
}
