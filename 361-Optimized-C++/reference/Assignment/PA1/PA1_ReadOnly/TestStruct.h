#pragma once

struct TestHotDog
{
	virtual ~TestHotDog() = default;

	TestHotDog *pNext;
	TestHotDog *pPrev;

	unsigned int condiments;
};


struct TestOrder
{
	virtual ~TestOrder() = default;

	TestOrder *pNext;
	TestOrder *pPrev;

	Name    name;
	TestHotDog *poHead;
};

struct TestStand
{
	virtual ~TestStand() = default;

	TestOrder *poHead;
	int numCurrentOrders;
	int numPeakOrders;
};