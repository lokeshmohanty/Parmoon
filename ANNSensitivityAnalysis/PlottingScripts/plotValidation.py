import os
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rc

# NOTE: get the correlation coefficients for all 50 experiments by running plotValidationCorrelation.py

def plotValid(runNumber, sampleNumber):
    #_______________________________________________________
    # Set paths and variables
    #_______________________________________________________
    currDir = os.getcwd();
    # Output path for sensitivity analysis (./output)
    outputPath = os.getcwd()+'/output';

    #_______________________________________________________
    # Plot for Expt1
    projectName = "Expt11"; # For Best L1, MS
    projectOutputDir = outputPath+'/'+projectName; 
    runDir = projectOutputDir+'/'+str(runNumber); 
    sampleDir = runDir+'/'+str(sampleNumber);
    data1 = np.loadtxt(sampleDir+"/testResults.csv",delimiter=',');

    #_______________________________________________________
    # Plot for Expt2
    projectName = "Expt12"; # For Best L1, MS
    projectOutputDir = outputPath+'/'+projectName; 
    runDir = projectOutputDir+'/'+str(runNumber); 
    sampleDir = runDir+'/'+str(sampleNumber);
    data2 = np.loadtxt(sampleDir+"/testResults.csv",delimiter=',');

    #_______________________________________________________
    # Plot for Expt3
    projectName = "Expt34"; # For Best L1, MS
    projectOutputDir = outputPath+'/'+projectName; 
    runDir = projectOutputDir+'/'+str(runNumber); 
    sampleDir = runDir+'/'+str(sampleNumber);
    data3 = np.loadtxt(sampleDir+"/testResults.csv",delimiter=',');


    s1color = 'red';
    s2color = 'green';
    s3color = 'darkblue';
    s4color = 'black';

    s1size = '5';
    s2size = '5';
    s3size = '5';
    s4size = '2';

    corr1 = np.corrcoef(data1[:,0], data1[:,1])[0,1];
    label1 = "Expt 1 (Corr: %0.2f"%corr1 + ")";
    corr2 = np.corrcoef(data2[:,0], data2[:,1])[0,1];
    label2 = "Expt 2 (Corr: %0.2f"%corr2 + ")";
    corr3 = np.corrcoef(data3[:,0], data3[:,1])[0,1];
    label3 = "Expt 3 (Corr: %0.2f"%corr3 + ")";


    # For plotting, split data into +ve & -ve
    data1p = data1[data1[:,1] > 0,:];
    data1n = data1[data1[:,1] < 0,:];
    data2p = data2[data2[:,1] > 0,:];
    data2n = data2[data2[:,1] < 0,:];
    data3p = data3[data3[:,1] > 0,:];
    data3n = data3[data3[:,1] < 0,:];

    plt.figure(figsize=(6.4,4.8), dpi=300, constrained_layout = True);


    plt.loglog(data1p[:,0], data1p[:,1],"o",color=s1color,markersize=s1size,label= label1);
    plt.loglog(data2p[:,0], data2p[:,1],"s",color=s2color,markersize=s2size,label=label2);
    plt.loglog(data3p[:,0], data3p[:,1],"^",color=s3color,markersize=s3size,label=label3);

    plt.loglog(data1n[:,0], abs(data1n[:,1]),"o",color="grey",markersize=s1size);
    plt.loglog(data2n[:,0], abs(data2n[:,1]),"s",color="grey",markersize=s2size);
    plt.loglog(data3n[:,0], abs(data3n[:,1]),"^",color="grey",markersize=s3size);

    lineData = np.linspace(10**-8, 1,1000);
    plt.plot(lineData, lineData,linewidth='1',color=s4color);

    plt.legend(loc=4, fontsize=20);

    plt.xlabel(r"$\tau^{ref}$", fontsize=24);
    #plt.xlim(10**-6, 1);
    #plt.ylim(10**-6, 1);

    plt.ylabel(r"$\tau^{ANN}$", fontsize=24);
    #print(np.corrcoef(data[:,0], data[:,1]));
    plt.grid();


    #plt.savefig("ValidBestMSE.pdf");
    plt.savefig("ValidWorstMSE.pdf");
    pass;


if __name__ == "__main__":
    from cycler import cycler

    plt.rcParams["text.usetex"] = True
    plt.rcParams["font.family"] = "serif"
    plt.rcParams["font.serif"] = ["Computer Modern"]

    plt.rcParams['xtick.labelsize'] = 20
    plt.rcParams['ytick.labelsize'] = 20
    plt.rcParams['axes.prop_cycle'] = cycler(color=['darkblue', '#d62728', '#2ca02c', '#ff7f0e', '#bcbd22', '#8c564b', '#17becf', '#9467bd', '#e377c2', '#7f7f7f'])


    ''' 
    # NOTE: get the correlation coefficients for all 50 experiments by running plotValidationCorrelation.py
    # BEST and WORST networks for all dataset sizes:
    # accoring to [L1, MS, Min, Max] errors
    __________________________________
    # TDS: 6
    Best Network for the Avg dataset:
    [4732, 4110, 1585, 1409]
    Worst Network for the Avg dataset:
    [2605, 17, 6597, 17]
    __________________________________
    # TDS: 12
    Best Network for the Avg dataset:
    [1565, 1491, 1455, 2037]
    Worst Network for the Avg dataset:
    [2605, 2605, 4673, 2605]
    __________________________________
    # TDS: 25
    Best Network for the Avg dataset:
    [1553, 4272, 7476, 2325]
    Worst Network for the Avg dataset:
    [2605, 2605, 4289, 3021]
    __________________________________
    # TDS: 50
    Best Network for the Avg dataset:
    [4450, 1045, 2281, 2325]
    Worst Network for the Avg dataset:
    [5821, 5821, 4093, 5821]
    __________________________________
    # TDS: 100
    Best Network for the Avg dataset:
    [1438, 1053, 3626, 2037]
    Worst Network for the Avg dataset:
    [6597, 6597, 6597, 6597]
    __________________________________
    # TDS: 200
    Best Network for the Avg dataset:
    [1702, 1041, 3391, 2037]
    Worst Network for the Avg dataset:
    [2365, 6597, 4601, 6597]
    __________________________________
    # TDS: 400
    Best Network for the Avg dataset:
    [1438, 1438, 6847, 2037]
    Worst Network for the Avg dataset:
    [2365, 4301, 4290, 3749]
    __________________________________
    # TDS: 800
    Best Network for the Avg dataset:
    [1438, 1557, 6418, 2037]
    Worst Network for the Avg dataset:
    [1500, 2365, 4290, 3749]
    __________________________________

    '''
    # Name of the project
    runNumber = 6; # TDS 400

    # Best MSE for TDS 400
    BestMSEID = 1438;
    # Worst MSE for TDS 400
    WorstMSEID = 4301;

    sampleNumber = BestMSEID;
    sampleNumber = WorstMSEID;

    # NOTE: get the correlation coefficients for all 50 experiments by running plotValidationCorrelation.py
    plotValid(runNumber, sampleNumber);
