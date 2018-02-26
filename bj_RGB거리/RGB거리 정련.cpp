#include <stdio.h>
/*
앞 코드의 문제점.
1. DP전의 경우 인덱스 0, 1을 정의할 때 0이 독립적이지 않음.
0에서 최소값을 잡아주고, 1에서 해당 색을 제외하고 최소값을 찾는 것은
1일때의 해당색을 썼을 때 최소값이 될 수 있다는 것을 포함하지 않음.

2. 또한 값이 동률일 경우, 어떤 색을 선택할 것인가에 대한 문제가 남아있음.

i의 값을 정할때, i - 1은 독립적이 아니다.
i - 2는 독립적인가? 
->DP를 쓸 수 있나?

일단 다 해보자.
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
	//해당 컬러를 제외하고 가장 최소값을 고르는 함수.
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
