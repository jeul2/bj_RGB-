#include <stdio.h>
/*
�� �ڵ��� ������.
1. DP���� ��� �ε��� 0, 1�� ������ �� 0�� ���������� ����.
0���� �ּҰ��� ����ְ�, 1���� �ش� ���� �����ϰ� �ּҰ��� ã�� ����
1�϶��� �ش���� ���� �� �ּҰ��� �� �� �ִٴ� ���� �������� ����.

2. ���� ���� ������ ���, � ���� ������ ���ΰ��� ���� ������ ��������.

i�� ���� ���Ҷ�, i - 1�� �������� �ƴϴ�.
i - 2�� �������ΰ�? 
->DP�� �� �� �ֳ�?

�ϴ� �� �غ���.
*/

struct S_HOUSE
{
	int nRed;
	int nGreen;
	int nBlue;
};


int fnMinValueExceptColor(int nExceptColor, const S_HOUSE * pSrcArray, int nIndex, int * pResValue, int *pResColor);

int main()
{
	int nData(0);
	S_HOUSE *p_sHouse(nullptr);
	int *parMinPath(nullptr);
	int *parPath(nullptr);

	int nHouseNumber(0);

	int nCurrentColor(0);
	int nCurrentValue(0);
	int nPreColor(0);

	int nResult(0);
	//
	freopen("input.txt", "r", stdin);
	scanf("%d", &nHouseNumber);

	p_sHouse = new S_HOUSE[nHouseNumber + 1]{};
	parMinPath = new int[nHouseNumber + 1]{};
	parPath = new int[nHouseNumber + 1]{};

	for (int i = 1; i <= nHouseNumber; ++i)
	{
		scanf("%d", &nData);
		p_sHouse[i].nRed = nData;
		scanf("%d", &nData);
		p_sHouse[i].nGreen = nData;
		scanf("%d", &nData);
		p_sHouse[i].nBlue = nData;
	}
	//////////////////
	//red 1, g 2 , b 3
	//�ش� �÷��� �����ϰ� ���� �ּҰ��� ���� �Լ�.
	parMinPath[0] = 100000;
	for (int j = 1; j <= 3; ++j)
	{

		parPath[0] = 0;
		for (int i = 1; i <= nHouseNumber; ++i)
		{
			if (i == 1)
			{
				fnMinValueExceptColor(j, p_sHouse, i, &nCurrentValue, &nCurrentColor);
			}
			else
			{
				fnMinValueExceptColor(nPreColor, p_sHouse, i, &nCurrentValue, &nCurrentColor);
			}

			parPath[i] = nCurrentValue;

			nPreColor = nCurrentColor;
			parPath[0] += parPath[i];
		}

		if (parMinPath[0] > parPath[0])
		{
			for (int i = 1; i <= nHouseNumber; ++i)
			{
				parMinPath[i] = parPath[i];
			}
			parMinPath[0] = parPath[0];
		}


	}



	//////////////////
	//

	for (int i = 1; i <= nHouseNumber; ++i)
	{
		printf("%d ", parMinPath[i]);
	}
	printf("\n");

	nResult = parMinPath[0];
	printf("%d\n", nResult);
	//
	delete[] parMinPath;
	parMinPath = nullptr;
	delete[] parPath;
	parPath = nullptr;
	delete[] p_sHouse;
	p_sHouse = nullptr;
	return 0;
}

int fnMinValueExceptColor(int nExceptColor, const S_HOUSE * pSrcArray, int nIndex, int * pResValue, int *pResColor)
{
	int nMinvalue(1000);
	int nSelectedColor(0);

	if (nExceptColor != 1 && pSrcArray[nIndex].nRed < nMinvalue)
	{
		nMinvalue = pSrcArray[nIndex].nRed;
		nSelectedColor = 1;
	}

	if (nExceptColor != 2 && pSrcArray[nIndex].nGreen < nMinvalue)
	{
		nMinvalue = pSrcArray[nIndex].nGreen;
		nSelectedColor = 2;
	}

	if (nExceptColor != 3 && pSrcArray[nIndex].nBlue < nMinvalue)
	{
		nMinvalue = pSrcArray[nIndex].nBlue;
		nSelectedColor = 3;
	}

	*pResColor = nSelectedColor;
	*pResValue = nMinvalue;
	return 0;
}
