#include <limits>

#include "CanDriveTwitter.h"
#include "JointPassive.h"

using namespace platform_driver_ethercat;

JointPassive::JointPassive(std::string name, std::shared_ptr<CanDriveTwitter>& drive, bool enabled)
    : Joint(name, drive, enabled) {}

bool JointPassive::commandPositionRad(double ) { return false; }

bool JointPassive::commandVelocityRadSec(double ) { return false; }

bool JointPassive::commandTorqueNm(double ) { return false; }

bool JointPassive::readPositionRad(double& position_rad)
{
    if (enabled_)
    {
        position_rad = drive_->readAuxiliaryPositionRad();
        return true;
    }
    else
    {
        position_rad = std::numeric_limits<double>::quiet_NaN();
        return false;
    }
}

bool JointPassive::readVelocityRadSec(double& velocity_rad_sec)
{
    if (enabled_)
    {
        // TODO
        velocity_rad_sec = 0.0;
        return true;
    }
    else
    {
        velocity_rad_sec = std::numeric_limits<double>::quiet_NaN();
        return false;
    }
}

bool JointPassive::readTorqueNm(double& torque_nm)
{
    torque_nm = std::numeric_limits<double>::quiet_NaN();
    return false;
}

bool JointPassive::readTempDegC(double& temp_deg_c)
{
    temp_deg_c = std::numeric_limits<double>::quiet_NaN();
    return false;
}
