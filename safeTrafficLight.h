#pragma once
/**
* CSC369 Assignment 2
*
* This is the header file for your safe traffic light submission code.
*/
#include "car.h"
#include "trafficLight.h"

/**
* @brief Structure that you can modify as part of your solution to implement
* proper synchronization for the traffic light intersection.
*
* This is basically a wrapper around TrafficLight, since you are not allowed to 
* modify or directly access members of TrafficLight.
*/
typedef struct _SafeTrafficLight {

	/**
	* @brief The underlying light.
	*
	* You are not allowed to modify the underlying traffic light or directly
	* access its members. All interactions must be done through the functions
	* you have been provided.
	*/
	TrafficLight base;

	// TODO: Add any members you need for synchronization here.

	/**
	* @brief The locks for entering lanes
	*/
	pthread_mutex_t enterLaneLocks[TRAFFIC_LIGHT_LANE_COUNT];
	/**
	* @brief The tokens for entering lanes
	*/
	int enterLaneTokens[TRAFFIC_LIGHT_LANE_COUNT];

	/**
	* @brief The locks for exiting lanes
	*/
	pthread_mutex_t exitLaneLocks[TRAFFIC_LIGHT_LANE_COUNT];
	/**
	* @brief The conditions for exiting lanes
	*/
	pthread_cond_t exitLaneConditions[TRAFFIC_LIGHT_LANE_COUNT];
	/**
	* @brief The tokens for exiting lanes
	*/
	int exitLaneTokens[TRAFFIC_LIGHT_LANE_COUNT];

	/**
	* @brief The locks for going through traffic light
	*/
	pthread_mutex_t goThroughTrafficLightLock;
	/**
	* @brief The conditions for going through traffic light
	*/
	pthread_cond_t goThroughTrafficLightCondition;

} SafeTrafficLight;

/**
* @brief Initializes the safe traffic light.
*
* @param light pointer to the instance of SafeTrafficLight to be initialized.
* @param eastWest total number of cars moving east-west.
* @param northSouth total number of cars moving north-south.
*/
void initSafeTrafficLight(SafeTrafficLight* light, int eastWest, int northSouth);

/**
* @brief Destroys the safe traffic light.
*
* @param light pointer to the instance of SafeTrafficLight to be destroyed.
*/
void destroySafeTrafficLight(SafeTrafficLight* light);

/**
* @brief Runs a car-thread in a traffic light scenario.
*
* @param car pointer to the car.
* @param light pointer to the traffic light intersection.
*/
void runTrafficLightCar(Car* car, SafeTrafficLight* light);
