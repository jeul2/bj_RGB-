
#include <stdio.h>

struct S_HOUSE
{
	int nRed;
	int nGreen;
	int nBlue;
};

struct S_COST
{
	int nSumRed;
	int nSumGreen;
	int nSumBlue;
};

int fnFindMinValue(int nSrc1, int nSrc2);
int fnFindMinValue(int nSrc1, int nSrc2, int nSrc3);

int main()
{
	int nInputHouseNum(0);
	S_HOUSE *pHouse(nullptr);
	S_COST *pCost(nullptr);
	int nData(0);

	//
	freopen("input.txt", "r", stdin);

	scanf("%d", &nInputHouseNum);
	pHouse = new S_HOUSE[nInputHouseNum + 1]{};
	pCost = new S_COST[nInputHouseNum + 1]{};

	for (int i = 1; i <= nInputHouseNum; ++i)
	{
		scanf("%d", &nData);
		pHouse[i].nRed = nData;
		scanf("%d", &nData);
		pHouse[i].nGreen = nData;
		scanf("%d", &nData);
		pHouse[i].nBlue = nData;
	}

	pCost[1].nSumRed = pHouse[1].nRed;
	pCost[1].nSumGreen = pHouse[1].nGreen;
	pCost[1].nSumBlue = pHouse[1].nBlue;

	for (int i = 2; i <= nInputHouseNum; ++i)
	{
		pCost[i].nSumRed = pHouse[i].nRed + fnFindMinValue(pCost[i - 1].nSumBlue, pCost[i - 1].nSumGreen);
		pCost[i].nSumGreen = pHouse[i].nGreen + fnFindMinValue(pCost[i - 1].nSumRed, pCost[i - 1].nSumBlue);
		pCost[i].nSumBlue = pHouse[i].nBlue + fnFindMinValue(pCost[i - 1].nSumRed, pCost[i - 1].nSumGreen);
	}

	nData = fnFindMinValue(pCost[nInputHouseNum].nSumRed, pCost[nInputHouseNum].nSumGreen, pCost[nInputHouseNum].nSumBlue);
	printf("%d\n", nData);

	delete[] pCost;
	pCost = nullptr;
	delete[] pHouse;
	pHouse = nullptr;

	return 0;
}

int fnFindMinValue(int nSrc1, int nSrc2)
{
	if (nSrc1 > nSrc2)
	{
		return nSrc2;
	}
	else
	{
		return nSrc1;
	}
}

int fnFindMinValue(int nSrc1, int nSrc2, int nSrc3)
{
	int nRes(0);
	int nData(0);
	nData = fnFindMinValue(nSrc1, nSrc2);
	nRes = fnFindMinValue(nData, nSrc3);
	return nRes;
}
