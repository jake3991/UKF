#include <iostream>
#include <stdexcept>
#include "Eigen/Dense"
#include "tools.h"
#include "ukf.h"

//using Eigen::VectorXd;
//using Eigen::MatrixXd;
//using namespace std;



    Tools::Tools() {}

    Tools::~Tools() {}

    Eigen::VectorXd Tools::CalculateRMSE(const std::vector<Eigen::VectorXd> &estimations,
                                  const std::vector<Eigen::VectorXd> &groundTruth)  {
        /**
        TODO:
          * Calculate the RMSE here.
        */
        VectorXd RSME(4);
        RSME << 0, 0, 0, 0;

        if (estimations.size() != groundTruth.size() || estimations.size() == 0) {

            return RSME;

        }

        for (unsigned int i = 0; i < estimations.size(); ++i) {

            VectorXd residual = estimations[i] - groundTruth[i];

            //coefficient-wise multiplication
            residual = residual.array() * residual.array();
            RSME += residual;
        }

        //calculate the mean
        RSME = RSME / estimations.size();

        //calculate the squared root
        RSME = RSME.array().sqrt();

        //return the RSME
        return RSME;

    }


    float CalculateNISPerformance(const std::vector<float> &nis_values, MeasurementPackage::SensorType sensorType) {
        const float nis_radar_95 = 7.815;
        const float nis_lidar_95 = 5.991;

        float limit_95 = sensorType == MeasurementPackage::RADAR ? nis_radar_95 : nis_lidar_95;

        int nis_over_95 = 0;
        for (int i = 0; i < nis_values.size(); i++) {
            if (nis_values[i] > limit_95) {
                nis_over_95++;
            }
        }

        return (nis_over_95 / (float) nis_values.size());
    }





