#define _USE_MATH_DEFINES
#include <Core/Application/Application.h>
#include <Core/UserInterface/UserInterface.h>
#include <Fusion/Fusion/Design.h>
#include <Fusion/Components/Joints.h>
#include <Fusion/Components/Joint.h>
#include <Fusion/Components/Component.h>
#include <Fusion/Components/RevoluteJointMotion.h>
#include <Core/Application/Viewport.h>
#include <Core/Utils.h>
#include <Core/Application/CustomEvents.h>
#include <thread>
#include <chrono>
#include <math.h>
#include "../motioncalc/MotionPerform.h"

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

using adsk::core::Ptr;
using adsk::core::Application;
using adsk::core::Product;
using adsk::core::UserInterface;
using adsk::core::Viewport;
using namespace adsk::fusion;

void writeAngles(double angles[4]);
void waitForMotion(int duration);
void update();
void dothings();
void stopit();

const double fps = 15; //frames per second
const double motorspeed = 4000; //microseconds per degree

Ptr<Application> app;
Ptr<UserInterface> ui;
Ptr<RevoluteJointMotion> motor1;
Ptr<RevoluteJointMotion> motor2;
Ptr<RevoluteJointMotion> motor3;
Ptr<RevoluteJointMotion> motor4; 
Ptr<adsk::core::CustomEvent> myevent;
std::thread thr1;
std::thread thr2;
double m1 = 0;
double m2 = 0;
double m3 = 0;
double m4 = 0;

MotionPerform perform(writeAngles, waitForMotion);

double destinedAngles[4];
bool finished = false;

class ThreadEventHandler : public adsk::core::CustomEventHandler {
public:
	void notify(const Ptr<adsk::core::CustomEventArgs>& eventArgs) override
	{
		if (eventArgs->additionalInfo().length() > 0)
		{
			adsk::terminate();
			return;
		}
		motor1->rotationValue(m1);
		motor2->rotationValue(m2);
		motor3->rotationValue(m3);
		motor4->rotationValue(m4);
	};
} onCustomEvent_;

void stopit() {
}

extern "C" XI_EXPORT bool run(const char* context)
{
	app = Application::get();
	if (!app)
		return false;

	ui = app->userInterface();
	if (!ui)
		return false;
	
	Ptr<Product> prod = app->activeProduct();
	if (!prod)
		return false;

	Ptr<Design> design = prod;
	if (!design)
		return false;

	Ptr<Component> rootComp = design->rootComponent();
	if (!rootComp)
		return false;

	Ptr<Joints> joints = rootComp->joints();
	if (!joints)
		return false;

	Ptr<Joint> mp1 = joints->itemByName("Motor1");
	Ptr<Joint> mp2 = joints->itemByName("Motor2");
	Ptr<Joint> mp3 = joints->itemByName("Motor3");
	Ptr<Joint> mp4 = joints->itemByName("Motor4");
	if (!mp1 || !mp2 || !mp3 || !mp4)
		return false;

	motor1 = mp1->jointMotion();
	motor2 = mp2->jointMotion();
	motor3 = mp3->jointMotion();
	motor4 = mp4->jointMotion();
	if (!motor1 || !motor2 || !motor3 || !motor4)
		return false;

	motor1->rotationValue(0);
	motor2->rotationValue(0);
	motor3->rotationValue(0);
	motor4->rotationValue(0);

	destinedAngles[0] = motor1->rotationValue();
	destinedAngles[1] = motor2->rotationValue();
	destinedAngles[2] = motor3->rotationValue();
	destinedAngles[3] = motor4->rotationValue();

	ui->messageBox("Start");

	thr1 = std::thread(update);
	thr2 = std::thread(dothings);

	thr1.detach();
	thr2.detach();

	Ptr<adsk::core::CustomEvent> myevent = app->registerCustomEvent("updateMotors");

	myevent->add(&onCustomEvent_);

	adsk::autoTerminate(false);

	return true;
}

void dothings() {
	perform.drawLine(Vector3D(2.5, 0, 5), Vector3D(2.5, 0, -5));
	app->fireCustomEvent("updateMotors", "stop");
}

void writeAngles(double angles[4]) {
	destinedAngles[0] = angles[0];
	destinedAngles[1] = angles[1];
	destinedAngles[2] = -angles[2];
	destinedAngles[3] = -angles[3];
}

void waitForMotion(int duration) {
	std::this_thread::sleep_for(std::chrono::milliseconds(duration));
}

void update() {
	const double framedur = 1000000.0 / fps; //in micros
	const double maxrot = framedur / motorspeed / 180 * M_PI;
	const int frdur = framedur;
	while (!finished) {
		auto t1 = std::chrono::high_resolution_clock::now();
		m1 = m1 > destinedAngles[0]
			? max(destinedAngles[0], m1 - maxrot)
			: min(destinedAngles[0], m1 + maxrot);
		m2 = m2 > destinedAngles[1]
			? max(destinedAngles[1], m2 - maxrot)
			: min(destinedAngles[1], m2 + maxrot);
		m3 = m3 > destinedAngles[2]
			? max(destinedAngles[2], m3 - maxrot)
			: min(destinedAngles[2], m3 + maxrot);
		m4 = m4 > destinedAngles[3]
			? max(destinedAngles[3], m4 - maxrot)
			: min(destinedAngles[3], m4 + maxrot);

		app->fireCustomEvent("updateMotors");
		std::this_thread::sleep_for(std::chrono::microseconds(frdur) - (std::chrono::high_resolution_clock::now() - t1));
	}
}

extern "C" XI_EXPORT bool stop(const char* context)
{
	if (myevent)
		myevent->remove(&onCustomEvent_);
	finished = true;
	if (thr2.joinable())
		thr2.join();
	if (thr1.joinable())
		thr1.join();
	if (app)
		app->unregisterCustomEvent("updateMotors");
	if (ui)
		ui->messageBox("Stop addin");
	ui = nullptr;
	app = nullptr;
	motor1 = nullptr;
	motor2 = nullptr;
	motor3 = nullptr;
	motor4 = nullptr;
	myevent = nullptr;
	return true;
}

#ifdef XI_WIN

#include <windows.h>

BOOL APIENTRY DllMain(HMODULE hmodule, DWORD reason, LPVOID reserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

#endif // XI_WIN