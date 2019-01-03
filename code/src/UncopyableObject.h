#ifndef UNCOPYABLEOBJECT_INCLUED
#define UNCOPYABLEOBJECT_INCLUED

/// This is a total interface to remove copy and assign operator for game object
/// This prevent the memories leeks
class UncopyableObject
{
protected:
	UncopyableObject() {}
	~UncopyableObject() {}
private:
	UncopyableObject(UncopyableObject& other) = delete;
	UncopyableObject& operator=(UncopyableObject& object) = delete;
};

#endif // UNCOPYABLEOBJECT_INCLUED