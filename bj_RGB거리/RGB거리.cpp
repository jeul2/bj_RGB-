#include <stdio.h>
#include <stdlib.h>

/*
제한, 전역변수 사용x
*/
struct S_HOUSE
{
	int nRed;
	int nGreen;
	int nBlue;
};

int fnFindMinValue(const S_HOUSE *pSrc, int nIndex, int * pResValue, int * pResColor, int nPreColor);
int fnFindSecondValue(const S_HOUSE *pSrc, int nIndex, int * pResValue, int * pResColor, int nPreColor, int nPrePreColor, const int *pDP, int nDPIndex);
int fnIsPreColored(int nPreColor, int nCurrentColor);

int fnPickAnotherColor(int nColor1, int nColor2, int *pResColor);

int main()
{
	int arDP[1000]{};// 1= red, 2= green, 3=blue
	int nTempDP(0);
	int nTempPreColor(0);

	int nData(0);
	S_HOUSE *p_sHouse(nullptr);

	int nHouseNumber(0);

	int nProcessValue(0); int nProcessColor(0);
	int nPreColor(0); int nPrePreColor(0);
	int nTempValue(0); int nTempColor(0);

	int nMinValue(0);
	//
	freopen("input.txt", "r", stdin);
	scanf("%d", &nHouseNumber);

	p_sHouse = (S_HOUSE *)malloc(sizeof(S_HOUSE) * nHouseNumber);

	for (int i = 0; i < nHouseNumber; ++i)
	{
		scanf("%d", &nData);
		p_sHouse[i].nRed = nData;
		scanf("%d", &nData);
		p_sHouse[i].nGreen = nData;
		scanf("%d", &nData);
		p_sHouse[i].nBlue = nData;
	}
	//
	if (nHouseNumber == 1)
	{
		fnFindMinValue(p_sHouse, 0, &nProcessValue, &nProcessColor, 0);
		arDP[0] = nProcessValue;
		nPreColor = nProcessColor;
		printf("%d\n", nProcessValue);
		return 0;
	}
	
	nProcessColor = 0;
	nProcessValue = 0;
	nTempColor = 0;
	nTempValue = 0;

	fnFindMinValue(p_sHouse, 0, &nProcessValue, &nProcessColor, 0);
	arDP[0] = nProcessValue;
	nPreColor = nProcessColor;

	fnFindMinValue(p_sHouse, 1, &nProcessValue, &nProcessColor, nPreColor);
	arDP[1] = arDP[0] + nProcessValue;
	nPrePreColor = nPreColor;
	nPreColor = nProcessColor;

	fnFindMinValue(p_sHouse, 1, &nTempValue, &nTempColor, 0);
	nTempDP = nTempValue;
	nTempPreColor = nTempColor;
	fnFindMinValue(p_sHouse, 0, &nTempValue, &nTempColor, nTempPreColor);
	nTempDP += nTempValue;
	//nTempPrePreColor = nTempPreColor;
	//nTempPreColor = nTempColor;

	if (nTempDP < arDP[1])
	{
		arDP[1] = nTempDP;
		nPreColor = nTempPreColor;
		nPrePreColor = nTempColor;

		if (nPrePreColor == 1)
			arDP[0] = p_sHouse[0].nRed;
		else if (nPrePreColor == 2)
			arDP[0] = p_sHouse[0].nGreen;
		else if (nPrePreColor == 3)
			arDP[0] = p_sHouse[0].nBlue;
	}



	for (int i = 2; i < nHouseNumber; ++i)
	{
		nProcessColor = 0;
		nProcessValue = 0;

		fnFindMinValue(p_sHouse, i, &nProcessValue, &nProcessColor, nPreColor);
		
		arDP[i] = arDP[i - 1] + nProcessValue;

		nTempColor = 0;
		nTempValue = 0;
		fnFindSecondValue(p_sHouse, i, &nTempValue, &nTempColor, nPreColor, nPrePreColor, arDP, i);

		if (arDP[i] >= nTempValue)
		{
			arDP[i] = nTempValue;
			fnPickAnotherColor(nPreColor, nPrePreColor, &nPrePreColor);
			nPreColor = nTempColor;
		}
		else
		{
			nPrePreColor = nPreColor;
			nPreColor = nProcessColor;
		}
	}
	
	nMinValue = arDP[nHouseNumber - 1];
	//

	printf("%d\n", nMinValue);

	free(p_sHouse);
	return 0;
}

int fnFindMinValue(const S_HOUSE * pSrc, int nIndex, int * pResValue, int * pResColor, int nPreColor)
{
	int nMin(1000);
	int nColor(0);

	
	if (nMin >= pSrc[nIndex].nRed && nPreColor != 1)
	{
		nMin = pSrc[nIndex].nRed;
		nColor = 1;
	}
	if (nMin >= pSrc[nIndex].nGreen && nPreColor != 2)
	{
		nMin = pSrc[nIndex].nGreen;
		nColor = 2;
	}
	if (nMin >= pSrc[nIndex].nBlue && nPreColor != 3)
	{
		nMin = pSrc[nIndex].nBlue;
		nColor = 3;
	}
	////////////////////////

	*pResValue = nMin;
	if (nColor == 1)
	{
		*pResColor = 1;
		return 1;
	}
	else if (nColor == 2)
	{

		*pResColor = 2;
		return 1;
	}
	else if (nColor == 3)
	{

		*pResColor = 3;
		return 1;
	}
	else
	{
		printf("fnMinvalue error\n");
		return 0;
	}

}

int fnFindSecondValue(const S_HOUSE * pSrc, int nIndex, int * pResValue, int * pResColor, int nPreColor, int nPrePreColor, const int *pDP, int nDPIndex)
{
	int nTempValue(0);
	int nTempColor(0);

	int nColor(0);
	int nValue(0);

	nColor = 0;
	fnPickAnotherColor(nPreColor, nPrePreColor, &nColor);
	nValue = pDP[nDPIndex - 2];
	if (nColor == 1)
	{
		nValue += pSrc[nIndex - 1].nRed;
	}
	else if (nColor == 2)
	{
		nValue += pSrc[nIndex - 1].nGreen;
	}
	else if (nColor == 3)
	{
		nValue += pSrc[nIndex - 1].nBlue;
	}
	

	fnFindMinValue(pSrc, nIndex, &nTempValue, &nTempColor, nColor);

	nValue += nTempValue;
	if (nTempColor == 1)
	{
		nValue += pSrc[nIndex].nRed;
	}
	else if (nTempColor == 2)
	{
		nValue += pSrc[nIndex].nGreen;
	}
	else if (nTempColor == 3)
	{
		nValue += pSrc[nIndex].nBlue;
	}

	*pResColor = nTempColor;
	*pResValue = nValue;

	return 0;
}

int fnIsPreColored(int nPreColor, int nCurrentColor)
{
	if (nPreColor == nCurrentColor)
		return 1;
	else
		return 0;
}

int fnPickAnotherColor(int nColor1, int nColor2, int * pResColor)
{
	if (nColor1 == 1 && nColor2 == 2)
		*pResColor = 3;
	else if (nColor1 == 1 && nColor2 == 3)
		*pResColor = 2;
	else if (nColor1 == 2 && nColor2 == 1)
		*pResColor = 3;
	else if (nColor1 == 2 && nColor2 == 3)
		*pResColor = 1;
	else if (nColor1 == 3 && nColor2 == 1)
		*pResColor = 2;
	else if (nColor1 == 3 && nColor2 == 2)
		*pResColor = 1;
	return 0;
}
