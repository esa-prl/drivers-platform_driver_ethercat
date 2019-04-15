#ifndef CANDRIVETWITTER_INCLUDEDEF_H
#define CANDRIVETWITTER_INCLUDEDEF_H



//* include files ---------------------------------------------

#include "CanOverEthercat.h"
#include "DriveParam.h"

/**
 * Interface description for a drive type of class.
 */
class CanDriveTwitter
{
public:
	/**
	 * The constructor
	 */
	CanDriveTwitter(CanOverEthercat *can_interface, std::string name);

	/**
	 * The destructor
	 */
	~CanDriveTwitter();

	/**
	 * Initializes the driver.
	 * Call this function once after construction.
	 * @return True if initialization was successful. False otherwise.
	 */
	bool init();
	
	/**
	 * Check if the driver is already initialized.
	 * This is necessary if a drive gets switched off during runtime.
	 * @return true if initialization occurred already, false if not.
	 */
	bool isInitialized();

	/**
	 * Brings the drive to operation enable state. 
	 * After calling the drive accepts velocity and position commands.
	 * @return True if drive is started successfully. StatusRegister is also evaluated to ensure a non-faulty state. False otherwise.
	 */
	bool startup();

	/**
	 * Brings the drive to switch on disabled state. 
	 * After calling the drive won't accepts velocity and position commands.
	 * @return True if drive shutdown successful.
	 */
	bool shutdown();

	/**
	 * Resets the drive.
	 * @return True if re-initialization was successful. False otherwise.
	 */
	bool reset();

	/**
	 * Sends position (and velocity) command (PTP Motion).
	 * Use this function only in position control mode.
	 * @param dPosRad Position command in Radians
	 * @param dVelRadS Velocity command in Radians/sec
	 */
	void positionCommandRad(double dPosRad, double dVelRadS);

	/**
	 * Sets the value for the reference position and velocity (PTP Motion).
	 * It does not execute the command. Useful for synchronized motion.
	 * Use this function only in position control mode.
	 * @param dPosRad Position setpoint in Radians.
	 * @param dVelRadS Velocity setpoint in Radians/sec.
	 * @see CommandSetPoint()
	 */
	void positionSetPointRad(double dPosRad, double dVelRadS);

	/**
	 * Sends velocity command.
	 * Use this function only in velocity control mode.
	 * @param dVelRadS Velocity command in Radians/sec.
	 */
	void velocityCommandRadS(double dVelRadS);

	/**
	 * Sets the value for the reference velocity.
	 * It does not execute the command. Useful for synchronized motion.
	 * Use this function only in velocity control mode.
	 * @param dVelRadS Velocity setpoint in Radians/sec.
	 * @see CommandSetPoint()
	 */
	void velocitySetPointRadS(double dVelRadS);

    /**
     * Sends Torque command
	 * Use this function only in torque control mode.
     * @param dTorqueNm is the required motor torque in Nm.
     */
    void torqueCommandNm(double dTorqueNm);

	/**
	 * Send execution command to start synchronized motion.
	 * @see positionSetPointRad()
	 * @see velocitySetPointRadS()
	 */
	void commandSetPoint();

    /**
     * Checks if the target set point was already reached.
     * @return True if the target set point was already reached.
     */
    bool checkTargetReached();

	/**
	 * Reads the last received value of the drive position.
	 * @return The value of the current position of the motor.
	 */
	double getPositionRad();

	/**
	 * Reads the last received value of the drive Velocity.
	 * @return The value of the current Velocity of the motor.
	 */
	double getVelocityRadS();

	/**
	 * Reads the last received value of the motor Torque.
	 * @return The value (in Nm) of the current motor torque is stored in this pointer.
	 */
	double getTorqueNm();

	/**
	 * Returns received value from analog input.
	 */
	double getAnalogInput();

	/**
	 * Returns true if an error has been detected.
	 * @return boolean with result.
	 */
	bool isError();
	
	/**
	 * Returns a bitfield containing information about the current error.
	 * @return unsigned int with bitcoded error.
	 */
	unsigned int getError();

	/**
	 * Enable the emergency stop.
	 * @return true if the result of the process is successful
	 */
	bool setEmergencyStop();

	/**
	 * Disable the emergency stop.
	 * @return true if the result of the process is successful
	 */
	bool resetEmergencyStop();

	/**
	 * Sets the drive parameters.
	 * @param driveParam is the object of the DriveParam class that contains the values of the drive parameters.
	 */
	void setDriveParam(DriveParam driveParam);

	/**
	 * Gets the drive parameters
	 * @return Pointer to the object of type DriveParam that is contained in the drive class.
	 */
	DriveParam *getDriveParam();

private:
    enum class DriveObject
    {
        // Error control objects
        ABORT_CONNECTION_OPTION_CODE = 0x6007;
        ERROR_CODE = 0x603f;

        // Device Control Objects
        CONTROL_WORD = 0x6040;
        STATUS_WORD = 0x6041;

        // Halt, stop and fault objects
        QUICK_STOP_OPTION_CODE = 0x605a;
        SHUTDOWN_OPTION_CODE = 0x605b;
        DISABLE_OPERATION_OPTION_CODE = 0x605c;
        HALT_OPTION_CODE = 0x605d;
        FAULT_REACTION_OPTION_CODE = 0x605e;

        // Modes of operation
        MODES_OF_OPERATION = 0x6060;
        MODES_OF_OPERATION_DISPLAY = 0x6061;
        SUPPORTED_DRIVE_MODES = 0x6502;

        // Position control
        POSITION_DEMAND_VALUE = 0x6062;
        POSITION_ACTUAL_INTERNAL_VALUE = 0x6063;
        POSITION_ACTUAL_VALUE = 0x6064;
        FOLLOWING_ERROR_WINDOW = 0x6065;
        FOLLOWING_ERROR_TIMEOUT = 0x6066;
        POSITION_WINDOW = 0x6067;
        POSITION_WINDOW_TIME = 0x6068;
        TARGET_POSITION = 0x607a;
        POSITION_RANGE_LIMIT = 0x607b;
        SOFTWARE_POSITION_LIMIT = 0x607d;
        MAX_PROFILE_VELOCITY = 0x607f;
        MAX_MOTOR_SPEED = 0x6080;
        PROFILE_VELOCITY = 0x6081;
        END_VELOCITY = 0x6082;
        PROFILE_ACCELERATION = 0x6083;
        PROFILE_DECELRATION = 0x6084;
        QUICK_STOP_DECELERATION = 0x6085;
        MOTION_PROFILE_TYPE = 0x6086;
        MAX_ACCELERATION = 0x60c5;
        MAX_DECELERATION = 0x60c6;
        POSITION_OPTION_CODE = 0x60f2;
        FOLLOWING_ERROR_ACTUAL_VALUE = 0x60f4;
        CONTROL_EFFORT = 0x60fa;
        POSITION_DEMAND_INTERNAL_VALUE_INCREMENTS = 0x60fc;

        // Velocity control
        VELOCITY_SENSOR_ACTUAL_VALUE = 0x6069;
        SENSOR_SELECTION_CODE = 0x606a;
        VELOCITY_DEMAND_VALUE = 0x606b;
        VELOCITY_ACTUAL_VALUE = 0x606c;
        VELOCITY_WINDOW = 0x606d;
        VELOCITY_WINDOW_TIME = 0x606e;
        VELOCITY_THRESHOLD = 0x606f;
        VELOCITY_THRESHOLD_TIME = 0x6070;
        TARGET_VELOCITY = 0x60ff;

        // Torque control
        TARGET_TORQUE = 0x6071;
        MAX_TORQUE = 0x6072;
        MAX_CURRENT = 0x6073;
        TORQUE_DEMAND_VALUE = 0x6074;
        MOTOR_RATE_CURRENT = 0x6075;
        MOTOR_RATE_TORQUE = 0x6076;
        TORQUE_ACTUAL_VALUE = 0x6077;
        CURRENT_ACTUAL_VALUE = 0x6078;
        DC_LINK_CIRCUIT_VOLTAGE = 0x6079;
        TORQUE_SLOPE = 0x6087;
        POSITIVE_TORQUE_LIMIT_VALUE = 0x60e0;
        NEGATIVE_TORQUE_LIMIT_VALUE = 0x60e1;

        // Factors
        POLARITY = 0x607e;
        POSITION_NOTATION_INDEX = 0x6089;
        POSITION_DIMENSION_INDEX = 0x608a;
        VELOCITY_NOTATION_INDEX = 0x608b;
        VELOCITY_DIMENSION_INDEX = 0x608c;
        ACCELERATION_NOTATION_INDEX = 0x608d;
        ACCELERATION_DIMENSION_INDEX = 0x608e;
        POSITION_ENCODER_RESOLUTION = 0x608f;
        VELOCITY_ENCODER_RESOLUTION = 0x6090;
        GEAR_RATIO = 0x6091;
        FEED_CONSTANT = 0x6092;
        POSITION_FACTOR = 0x6093;
        VELOCITY_ENCODER_FACTOR = 0x6094;
        VELOCITY_FACTOR_1 = 0x6095;
        VELOCITY_FACTOR = 0x6096;
        ACCELERATION_FACTOR = 0x6097;

        // Cyclic synchronous modes
        POSITION_OFFSET = 0x60b0;
        VELOCITY_OFFSET = 0x60b1;
        TORQUE_OFFSET = 0x60b2;

        // Drive data objects
        ANALOG_INPUT = 0x2205;
        DIGITAL_INPUTS = 0x60fd;
        DIGITAL_OUTPUTS = 0x60fe;
    }

	/**
	 * States of the CANOpen drive state machine.
	 */
	enum DriveState
	{
		ST_NOT_READY_TO_SWITCH_ON,
		ST_SWITCH_ON_DISABLED,
		ST_READY_TO_SWITCH_ON,
		ST_SWITCHED_ON,
		ST_OPERATION_ENABLE,
		ST_QUICK_STOP_ACTIVE,
        ST_FAULT_REACTION_ACTIVE,
		ST_FAULT
	};

	/**
	 * Enum with different operation modes of the controller, either position, velocity or torque control.
	 */
	enum OperationMode
	{
		OM_PROFILE_POSITION = 1,
        OM_PROFILE_VELOCITY = 3,
        OM_PROFILE_TORQUE = 4,
		OM_CYCSYNC_POSITION = 8,
        OM_CYCSYNC_VELOCITY = 9,
        OM_CYCSYNC_TORQUE = 10
	};

    typedef struct RxPDO
    {
        uint16 control_word;
        uint16 operation_mode;
        int32 target_position;
        int32 target_velocity;
        int16 target_torque;
    } RxPDO;

    typedef struct TxPDO
    {
        uint16 status_word;
        uint8 operation_mode_display;
        int32 actual_position;
        int32 actual_velocity;
        int16 actual_torque;
        int16 analog_input;
    } TxPDO;

    CanOverEthercat *_can_interface;
    std::string _device_name;
    RxPDO *output;
    TxPDO *input;

	/**
	 * Returns the state of the drive
	 */
	DriveState getDriveState();
    OperationMode getOperationMode()
    bool setOperationMode(OperationMode mode)
};

//-----------------------------------------------
#endif
