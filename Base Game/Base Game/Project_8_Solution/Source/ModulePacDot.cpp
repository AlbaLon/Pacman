//#include "ModulePacDot.h"
//
//#include "Application.h"
//#include "ModuleTextures.h"
//#include "Enemy.h"
//#include "ModuleRender.h"
//#include "ModuleAudio.h"
//#include "ModuleCollisions.h"
//#include "ModuleFadeToBlack.h"
//#include "SceneLevel1.h"
//
//Pacdot::ModulePacDot()
//{
//	position.SetToZero();
//	
//}
//
//Pacdot::ModulePacDot(const Pacdot& p) : idleAnim(p.idleAnim), position(p.position),
//frameCount(p.frameCount), lifetime(p.lifetime)
//{
//
//}
//
//Pacdot::~ModulePacDot()
//{
//	if (collider != nullptr)
//		collider->pendingToDelete = true;
//}
//
//bool Particle::Update()
//{
//	bool ret = true;
//	frameCount++;
//
//	// The particle is set to 'alive' when the delay has been reached
//	if (!isAlive && frameCount >= 0)
//		isAlive = true;
//
//	if (isAlive)
//	{
//		idleAnim.Update();
//
//		// If the particle has a specific lifetime, check when it has to be destroyed
//		if (lifetime > 0)
//		{
//			if (frameCount >= lifetime)
//				ret = false;
//		}
//		// Otherwise the particle is destroyed when the animation is finished
//		else if (idleAnim.HasFinished())
//			ret = false;
//
//		
//
//		if (collider != nullptr)
//			collider->SetPos(position.x, position.y);
//	}
//
//	return ret;
//}