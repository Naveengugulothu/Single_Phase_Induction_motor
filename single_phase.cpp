#include <iostream>
#include <cmath>

using namespace std;

void getdata(int& freq, int& synsp, float& powin, float& volt) {
    cout << "Enter frequency: ";
    cin >> freq;
    cout << "Enter synchronous speed(in rps): ";
    cin >> synsp;
    cout << "Enter power input(in hp): ";
    cin >> powin;
    cout << "Enter supply voltage: ";
    cin >> volt;
}

void display(int freq, int synsp, float powin, float volt) {
    cout << endl << "Frequency = " << freq << ", synchronous speed = " << synsp << " r.p.s"
        << ", power output = " << powin << ", supply voltage = " << volt;
}

void stator(int freq, int synsp, float powin, float volt) {
    long ac;
    float Bav;
    float pf, effy, Kwm;

    cout << endl << "Enter the value of ac: ";
    cin >> ac;
    cout << "Enter the value of Bav: ";
    cin >> Bav;
    cout << "Enter the value of winding factor (main winding): ";
    cin >> Kwm;
    cout << "Enter the value of power factor: ";
    cin >> pf;
    cout << "Enter the value of efficiency: ";
    cin >> effy;

    int p;
    float  DsqL, dd, D, L,ss;
    const float PI = 3.14159f;
    int co;
    co = 11 * Kwm * Bav * ac * 0.001;
    DsqL = powin * 0.746 / (effy * pf * co * freq);

    cout << endl << "DSqL: " << DsqL << endl;
    cout<<endl;
    p = static_cast<int>(2 * freq / synsp);
    dd = (DsqL) * p / PI;
    D = pow(dd, 0.333);
    L = PI * D / p;
    cout << "Computed stator inside Diameter in m: " << D;
    cout << endl << "Computed Stator Length in m: " << L<<"m"<<endl;
    cout<<endl<<endl;
    cout<<"CHOOSE NUMBER OF STATOR SLOTS :";
    cin>>ss;
    double nL;
    nL=0.95*L;
    cout<<endl<<endl;
    cout<<"Net iron length : "<<nL<<"m"<<endl;
    cout<<"Pole Pitch :"<<L<<"m"<<endl;
    double sp;
    sp=PI*D/ss;
    cout<<"Stator Slot pitch : "<<sp<<"m"<<endl;
    double fpp;
    fpp=(Bav*PI*D*L)/(p);
    cout<<"Flux per Pole :"<<fpp<<"Wb/m2"<<endl;
    cout<<"Flux density in the stator core :"<<fpp/2<<endl;
    double wst, ratio,dss,dsc,Di,fdst;
    wst=fpp/(1.7*(ss/p)*nL);
    cout<<"Width of the stator tooth :"<<wst<<endl; 
    cout<<endl<<endl;
    cout<<"Enter the ratio of Di/Do = ";
    cin>>ratio;
    Di=ratio*D;
    cout<<"Inside diameter of the stator is :"<<Di<<endl;
    cout<<"Enter the depth  of the Stator slot :";
    cin>>dss;
    dsc=(D-Di-2*dss)/2;
    cout<<"Depth of the Stator Core is ="<<dsc<<endl;
    fdst=(fpp)/((ss/p)*nL*wst);
    cout<<"Flux density in the Stator teeth is ="<<fdst<<endl;
    //Stator Main Winding 
    double E,Tm,Tpm;
    E=0.95*volt;
    cout<<endl<<endl;
    cout<<"Stator main winding Dimensions are :"<<endl;
    cout<<"Induced emf E :"<<E<<endl;
    Tm=E/(4.44*Kwm*freq*fpp);
    cout<<"Number of series turns in main winding :"<<Tm<<endl;
    Tpm=Tm/p;
    cout<<"Turns in Series per Pole :"<<Tpm<<endl;
    //Winding arrangement for stator main winding
    double Ssp,C46,C37,C28,C19;
    double cN46,cN37,cN28,cN19,add;
    Ssp=ss/p;
    C46=sinf((2.*PI)/(2.*Ssp));
    C37=sinf((4.*PI)/(2.*Ssp));
    C28=sinf((6.*PI)/(2.*Ssp));
    C19=sinf((8.*PI)/(2.*Ssp));
    add=C46+C37+C28+C19;
    cN46=(C46/add)*Tpm;
    cN37=(C37/add)*Tpm;
    cN28=(C28/add)*Tpm;
    cN19=(C19/add)*Tpm;
    cout<<"The Turns in each coil are "<<endl;
    cout<<"Coil 4--6 : "<<cN46<<endl;
    cout<<"Coil 3--7 : "<<cN37<<endl;
    cout<<"Coil 2--8 : "<<cN28<<endl;
    cout<<"Coil 1--9 : "<<cN19<<endl;
    double add1,Nm;
    add1=cN46+cN37+cN28+cN19;
    Nm=add1*p;
    cout<<"Total turns in series for main winding (Tm) :"<<Nm<<endl;
    cout<<"Total turns in series per pole :"<<add1<<endl;
    Kwm=(cN46*C46+cN37*C37+cN28*C28+cN19*C19)/(add1);
    cout<<"Winding factor of Main winding ="<<Kwm<<endl;
    //Main winding conductor  size 
    cout<<endl<<endl;
    double Im,Id,area,dia;
    Im=powin*746/(volt*effy*pf);
    cout<<"Enter the Current density(Usually lies between 3 to 5 A/mm2) =";
    cin>>Id;
    area=Im/Id;
    dia=sqrt(4*area/PI);
    cout<<"Current in the main winding :"<<Im<<" "<<"A"<<endl;
    cout<<"Area of the main winding conductor ="<<area<<" "<<"mm2"<<endl;
    cout<<"Diameter of the main winding conductor :"<<dia<<"mm"<<endl;
    cout<<"Diameter of the insulated conductor : "<<dia+0.063<<" "<<"mm"<<endl;
    //Length of mean Turn of main winding
    double Lm19,Lm28,Lm37,Lm46;
    Lm19=8.4*((D+dss)/ss)*(8+(2*L));
    Lm28=8.4*((D+dss)/ss)*(6+(2*L));
    Lm37==8.4*((D+dss)/ss)*(4+(2*L));
    Lm46==8.4*((D+dss)/ss)*(2+(2*L));
    cout<<"Length of mean turn of coil (1--9) : "<<Lm19<<endl;
    cout<<"Length of mean turn of coil (2--8) : "<<Lm28<<endl;
    cout<<"Length of mean turn of coil (3--7) : "<<Lm37<<endl;
    cout<<"Length of mean turn of coil (4--6) : "<<Lm46<<endl;


    //Rotor Design
    double lg,Rd,Rs,Rsp,Ar1,Ar,Am;
    cout<<endl<<endl;
    cout<<"Enter the number  of Rotor Slots :";
    cin>>Rs;
    lg=(0.007*D)/(sqrt(p));
    Rd=Di-2*lg;
    Rsp=(PI*Rd)/(Rs);
    Am=2*Nm*area;
    cout<<"Length of the air gap is :"<<lg<<endl;
    cout<<"Diameter of the rotor is  :"<<Rd<<endl;
    cout<<"Rotor slot pitch is : "<<Rsp<<endl;
    cout<<"Enter the area of Rotor bar :";
    cin>>Ar1;
    Ar=Ar1*Rs;
    cout<<endl<<endl;
    cout<<"Total area of the Rotor bar :"<<Ar<<endl; 
    cout<<"Total area  of the of Conductors of main winding :"<<Am<<endl;
    cout<<"Ratio(Ar/Am) :"<<(Ar*Rs)/(Am)<<endl;


    //End ring
    cout<<endl<<endl;
    double Ae,de,te,ae,dero,deri,mean;
    Ae=(0.32*Ar)/(p);
    dero=D-0.001;
    deri=D-(2*de*0.001);
    mean=(dero+deri)/(2);
    cout<<"Area of each end ring :"<<Ae<<"mm2"<<endl;
    cout<<"Enter the depth of end ring (in mm):";
    cin>>de;
    cout<<"Enter the thickness of end ring(in mm):";
    cin>>te;
    cout<<"Area of each End Ring :"<<de*te<<"mm2"<<endl;
    cout<<"Outer diameter of End Ring :"<<dero<<"m"<<endl;
    cout<<"Inner diameter of End Ring :"<<deri<<"m"<<endl;
    cout<<"Mean diameter of End Ring :"<<mean<<"m"<<endl;
    cout<<endl<<endl;
    cout<<"THE END";

    //Gap Contractions factor
   /*double wos,Kos,Kgss,wor,ratio1,Kcs,Kgrs,Kg;
    wos=2.29*0.001;// in meter
    ratio1=wos/lg;
    cout<<"Enter the Carter's Coefficent for Semi conductors slots (around 0.7):";
    cin>>Kos;
    cout<<endl;
    cout<<"Stator slot opening :"<<wos<<"m"<<endl;
    cout<<"Ratio of stator slots opening and gap length :"<<ratio1<<endl; */








    















    




}

int main() {
    int freq, synsp;
    float powin, volt;

    getdata(freq, synsp, powin, volt);
    display(freq, synsp, powin, volt);
    stator(freq, synsp, powin, volt);

    return 0;
}
