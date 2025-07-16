#include "collisionHandling.h"

#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>

#include "ActiveObj.h"
#include "PassiveObj.h"
#include "ThrowableObj.h"
#include "SpacielAttack.h"
#include "Player.h"
#include "AutoObj.h"

namespace // anonymous namespace — the standard way to make function "static"
{

    // primary collision-processing functions
    void ActiveObjActiveObj(GameObj& ActiveObj1,
        GameObj& ActiveObj2)
    {

        ActiveObj& obj1 = dynamic_cast<ActiveObj&>(ActiveObj1);
        ActiveObj& obj2 = dynamic_cast<ActiveObj&>(ActiveObj2);
        if (obj1.areEnemyTeam() != obj2.areEnemyTeam())
        {
            if (obj1.getAttackPower() > 0 && obj2.getAttackPower() == 0)
            {
                obj2.getHurt(obj1.getAttackPower());
            }
            else if (obj1.getAttackPower() == 0 && obj2.getAttackPower() > 0)
            {
                obj1.getHurt(obj2.getAttackPower());
            }
        }
    }
    //--------------------------------------------------
    void ActiveObjPassiveObj(GameObj& activeObj,
        GameObj& passiveObj)
    {
        ActiveObj& obj1 = dynamic_cast<ActiveObj&>(activeObj);
        PassiveObj& obj2 = dynamic_cast<PassiveObj&>(passiveObj);
        if (obj1.areEnemyTeam() != obj2.areEnemyTeam())
        {
            if (obj2.getAttackPower() < 0)
                return;
            else if (obj1.getAttackPower() > 0)
                obj2.getHurt(obj1.getAttackPower());
            else if (obj1.getAttackPower() == 0)
                obj1.getHurt(obj2.getAttackPower());
        }

    }
    //--------------------------------------------------
    void ActiveObjThrowAble(GameObj& activeObj,
        GameObj& ThrowAble)
    {
        ActiveObj& active = dynamic_cast<ActiveObj&>(activeObj);
        ThrowableObj& throwable = dynamic_cast<ThrowableObj&>(ThrowAble);
        if (active.areEnemyTeam() != throwable.areEnemyTeam())
        {
            if (active.getAttackPower() >= 0 && throwable.getAttackPower() > 0)
            {
                active.getHurt(throwable.getAttackPower());
                throwable.destroyBall();
            }
        }
    }
    //--------------------------------------------------
    void ActiveObjspacielAttack(GameObj& activeObj,
        GameObj& spacielAttack)
    {
        ActiveObj& active = dynamic_cast<ActiveObj&>(activeObj);
        SpacielAttack& spaciel = dynamic_cast<SpacielAttack&>(spacielAttack);
        if (active.getAttackPower() >= 0 && spaciel.isHit())
        {
            active.getHurt(spaciel.getAttackPower());
        }
    }
    //--------------------------------------------------
    void PassiveObjSpaceilAttack(GameObj& passiveObj,
        GameObj& spacielAttack)
    {
        PassiveObj& passive = dynamic_cast<PassiveObj&>(passiveObj);
        SpacielAttack& spaciel = dynamic_cast<SpacielAttack&>(spacielAttack);
        if (passive.getAttackPower() >= 0 && spaciel.isHit())
        {
            passive.getHurt(spaciel.getAttackPower());
        }
    }
    //--------------------------------------------------
    void PassiveObjThrowAble(GameObj& passiveObj,
        GameObj& throwAble)
    {
        PassiveObj& passive = dynamic_cast<PassiveObj&>(passiveObj);
        ThrowableObj& throwable = dynamic_cast<ThrowableObj&>(throwAble);
        if (passive.areEnemyTeam() != throwable.areEnemyTeam())
        {
            if (passive.getAttackPower() >= 0 && throwable.getAttackPower() > 0)
            {
                passive.getHurt(throwable.getAttackPower());
                throwable.destroyBall();
            }
        }
    }

    // secondary collision-processing functions that just
    // implement symmetry: swap the parameters and call a
    // primary function
    void PassiveObjActiveObj(GameObj& passiveObj,
        GameObj& activeObj)
    {
        ActiveObjPassiveObj(activeObj, passiveObj);
    }
    //--------------------------------------------------
    void ThrowAbleActiveObj(GameObj& throwAble,
        GameObj& activeObj)
    {
        //std::cout << "ThrowAble and ActiveObj collision!\n";
        ActiveObjThrowAble(activeObj, throwAble);
    }
    //--------------------------------------------------
    void spacielAttackActiveObj(GameObj& spacielAttack,
        GameObj& activeObj)
    {
        ActiveObjspacielAttack(activeObj, spacielAttack);
    }
    //--------------------------------------------------
    void SpaceilAttackPassiveObj(GameObj& spacielAttack,
        GameObj& passiveObj)
    {
        PassiveObjSpaceilAttack(passiveObj, spacielAttack);
    }
    //--------------------------------------------------
    void ThrowAblePassiveObj(GameObj& throwAble,
        GameObj& passiveObj)
    {
        PassiveObjThrowAble(passiveObj, throwAble);
    }
    

    using HitFunctionPtr = std::function<void(GameObj&, GameObj&)>;
    using Key = std::pair<std::type_index, std::type_index>;
    using HitMap = std::map<Key, HitFunctionPtr>;

    HitMap initializeCollisionMap()
    {
        HitMap phm;
        phm[Key(typeid(AutoObj), typeid(AutoObj))] = &ActiveObjActiveObj;
        phm[Key(typeid(AutoObj), typeid(PassiveObj))] = &ActiveObjPassiveObj;
        phm[Key(typeid(Player), typeid(AutoObj))] = &ActiveObjActiveObj;
        phm[Key(typeid(Player), typeid(PassiveObj))] = &ActiveObjPassiveObj;
        phm[Key(typeid(AutoObj), typeid(ThrowableObj))] = &ActiveObjThrowAble;
        phm[Key(typeid(Player), typeid(ThrowableObj))] = &ActiveObjThrowAble;
        phm[Key(typeid(AutoObj), typeid(SpacielAttack))] = &ActiveObjspacielAttack;
        phm[Key(typeid(Player), typeid(SpacielAttack))] = &ActiveObjspacielAttack;
        phm[Key(typeid(PassiveObj), typeid(SpacielAttack))] = &PassiveObjSpaceilAttack;
        phm[Key(typeid(PassiveObj), typeid(AutoObj))] = &PassiveObjActiveObj;
        phm[Key(typeid(PassiveObj), typeid(Player))] = &PassiveObjActiveObj;
        phm[Key(typeid(PassiveObj), typeid(ThrowableObj))] = &PassiveObjThrowAble;
        phm[Key(typeid(SpacielAttack), typeid(AutoObj))] = &spacielAttackActiveObj;
        phm[Key(typeid(SpacielAttack), typeid(Player))] = &spacielAttackActiveObj;
        phm[Key(typeid(SpacielAttack), typeid(PassiveObj))] = &SpaceilAttackPassiveObj;
        phm[Key(typeid(ThrowableObj), typeid(PassiveObj))] = &ThrowAblePassiveObj;
        phm[Key(typeid(ThrowableObj), typeid(AutoObj))] = &ThrowAbleActiveObj;
        phm[Key(typeid(ThrowableObj), typeid(Player))] = &ThrowAbleActiveObj;
        return phm;
    }

    HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
    {
        static HitMap collisionMap = initializeCollisionMap();
        auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
        if (mapEntry == collisionMap.end())
        {
            return nullptr;
        }
        return mapEntry->second;
    }

} // end namespace

void processCollision(GameObj& object1, GameObj& object2)
{
    auto phf = lookup(typeid(object1), typeid(object2));
    if (!phf)
    {
        //return;
        throw UnknownCollision(object1, object2);
    }
    phf(object1, object2);
}