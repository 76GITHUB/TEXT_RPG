#include <iostream>
#include <time.h>
using namespace std;

enum MAIN_MENU //메인메뉴 열거형
{
	MM_NONE, 
	MM_MAP,  //멥선택
	MM_STORE,//상점
	MM_INVENTORY,//가방
	MM_EXIT//나가기
};

enum MAP_TYPE //맵선택 열거형
{
	MT_NONE,
	MT_EASY,//쉬움
	MT_NORMAL,//보통
	MT_HARD,//어려움
	MT_BACK//나가기
};

enum JOB //플레이어 직업선택을 위한 열거형
{
	JOB_NONE,
	JOB_KNIGHT,//기사
	JOB_ARCHER,//궁수
	JOB_WIZARD,//마법사
	JOB_END
};

enum EQUIP //장착한 아이템 열거형
{
	EQ_WEAPON, //무기
	EQ_ARMOR, //방어구
	EQ_MAX
};

enum ITEM_TYPE //아이템타입 열거형
{
	IT_NONE,
	IT_WEAPON, //무기
	IT_ARMOR,//방어구
	IT_BACK
};

enum BATTLE
{
	BATTLE_NONE,
	BATTLE_ATTACK, //공격
	BATTLE_BACK //도망
};

enum STORE_MENU
{
	SM_NONE,
	SM_WEAPON,
	SM_ARMOR,
	SM_BACK
};

//매크로 정의 각각의 사이즈들을 정해준다.
#define	NAME_SIZE	32 //이름길이
#define	ITEM_DESC_LENGTH	512 //아이템설명길이
#define	INVENTORY_MAX		20 //인벤토리최대크기
#define	STORE_WEAPON_MAX	3 //상점무기최대크기
#define	STORE_ARMOR_MAX		3//상점방어구최대크기
#define	LEVEL_MAX			10//맥스레벨크기

struct _tagItem //아이템 구조체
{
	char	strName[NAME_SIZE]; //아이템이름
	char	strTypeName[NAME_SIZE];//아이템속성이름
	ITEM_TYPE	eType;//아이템 타입 열거형 변수를 선언
	int		iMin;
	int		iMax;
	int		iPrice;
	int		iSell;
	char	strDesc[ITEM_DESC_LENGTH];
};

struct _tagInventory //인벤토리 구조체
{
	_tagItem	tItem[INVENTORY_MAX]; 
	int			iItemCount;
	int			iGold;
};

struct _tagPlayer //플레이어 구조체
{
	char	strName[NAME_SIZE]; //플레이어 이름
	char	strJobName[NAME_SIZE];//플레이어 직업이름
	JOB		eJob; //직업 열거형 변수
	int		iAttackMin;
	int		iAttackMax;
	int		iArmorMin;
	int		iArmorMax;
	int		iHP;
	int		iHPMax;
	int		iMP;
	int		iMPMax;
	int		iExp;
	int		iLevel;
	_tagItem	tEquip[EQ_MAX];
	bool		bEquip[EQ_MAX];
	_tagInventory	tInventory;
};

struct _tagMonster // 몬스터 구조체
{
	char	strName[NAME_SIZE];
	int		iAttackMin;
	int		iAttackMax;
	int		iArmorMin;
	int		iArmorMax;
	int		iHP;
	int		iHPMax;
	int		iMP;
	int		iMPMax;
	int		iLevel;
	int		iExp;
	int		iGoldMin;
	int		iGoldMax;
};

struct _tagLevelUpStatus 
{
	int	iAttackMin;
	int	iAttackMax;
	int	iArmorMin;
	int	iArmorMax;
	int	iHPMin;
	int	iHPMax;
	int	iMPMin;
	int	iMPMax;
};

const int	iLevelUpExp[LEVEL_MAX] = { 4000, 10000, 20000, 35000, 50000, 70000, 100000, 150000, 200000, 400000 };
//경험치 테이블 전역변수

_tagLevelUpStatus tLvUpTable[JOB_END - 1] = {};

int Input() { //메뉴나 전투등등 입력을 받기위한 함수
	int iInput; 
	cin >> iInput;//입력

	if (cin.fail()) //정수가 아닌 값을 입력받을때 예외처리
	{
		cin.clear(); //에러 버퍼 클리어
		cin.ignore(1024, '\n'); // \n입력전까지의 버퍼를 삭제
		return INT_MAX;  //INT_MAX가 리턴되면 잘못된값을 입력했다는 의미
	}
	return iInput;
}

int OPMainMenu() { //메인메뉴를 보여는함수, 그리고 입력받은 메뉴를 반환한다
	system("cls"); //잘못된 메뉴를 입력한경우에는 MM_NONE반환
	cout << "*************************** 로비 ***************************" << endl;
	cout << "1. 맵" << endl;
	cout << "2. 상점" << endl;
	cout << "3. 가방" << endl;
	cout << "4. 종료" << endl;
	cout << "메뉴를 선택하세요 : ";
	int imenu = Input(); //Input함수를 호출하여 반환받은값을 imenu에 값으로 초기화

	if (imenu == INT_MAX || imenu <= MM_NONE || imenu > MM_EXIT) //imenu가 INT_MAX값이거나 MM_NONE=0 이하이거나
		return MM_NONE; //MM_EXIT=4보다 클경우에는 MM_NONE이다.

	return imenu;
}

int OPMapMenu() {
	system("cls");
	cout << "*************************** 맵 ***************************" << endl;
	cout << "1. 쉬움" << endl;
	cout << "2. 보통" << endl;
	cout << "3. 어려움" << endl;
	cout << "4. 뒤로가기" << endl;
	cout << "맵을 선택하세요 : ";

	int imenu = Input(); //Input함수를 호출하여 반환받은값을 imenu에 값으로 초기화

	if (imenu == INT_MAX || imenu <= MT_NONE || imenu > MT_BACK) //imenu가 INT_MAX값이거나 MT_NONE=0 이하이거나
	  return MT_NONE; //MT_EXIT=4보다 클경우에는 MT_NONE이다.

	return imenu;

}

int SJob() { //직업을 선택하기위한 함수
	int	iJob = JOB_NONE; //기본세팅
	while (iJob == JOB_NONE) // 무한루프를 돌리기위함
	{
		system("cls");
		cout << "1. 기사" << endl;
		cout << "2. 궁수" << endl;
		cout << "3. 마법사" << endl;
		cout << "직업을 선택하세요 : ";
		iJob = Input();//Input함수를 호출하여 값을 받아온다


		if (iJob == INT_MAX || iJob <= JOB_NONE || iJob >= JOB_END)
			iJob = JOB_NONE;
	}
	return iJob; //올바른 값을 입력했다면 입력한 값에대한 직업을 반환한다.
}

void SetPlayer(_tagPlayer * pPlayer) { //call-by-address

	cout << "이름 : ";   // 플레이어 이름을 입력받는다.
	cin.getline(pPlayer->strName, NAME_SIZE - 1);

	pPlayer->eJob = (JOB)SJob(); //SJob함수는 int를 반환하지만eJob은 JOB타입 변수이므로 형변환을 시켜준다.
	pPlayer->iLevel = 1;
	pPlayer->iExp = 0;
	pPlayer->tInventory.iGold = 10000;

	switch (pPlayer->eJob)
	{
	case JOB_KNIGHT:
		strcpy_s(pPlayer->strJobName, "기사");
		pPlayer->iAttackMin = 5;
		pPlayer->iAttackMax = 10;
		pPlayer->iArmorMin = 15;
		pPlayer->iArmorMax = 20;
		pPlayer->iHPMax = 500;
		pPlayer->iHP = 500;
		pPlayer->iMP = 100;
		pPlayer->iMPMax = 100;
		break;
	case JOB_ARCHER:
		strcpy_s(pPlayer->strJobName, "궁수");
		pPlayer->iAttackMin = 10;
		pPlayer->iAttackMax = 15;
		pPlayer->iArmorMin = 10;
		pPlayer->iArmorMax = 15;
		pPlayer->iHPMax = 400;
		pPlayer->iHP = 400;
		pPlayer->iMP = 200;
		pPlayer->iMPMax = 200;
		break;
	case JOB_WIZARD:
		strcpy_s(pPlayer->strJobName, "마법사");
		pPlayer->iAttackMin = 15;
		pPlayer->iAttackMax = 20;
		pPlayer->iArmorMin = 5;
		pPlayer->iArmorMax = 10;
		pPlayer->iHPMax = 300;
		pPlayer->iHP = 300;
		pPlayer->iMP = 300;
		pPlayer->iMPMax = 300;
		break;

	}

}

void BattleMode(int imenu) { //배틀난이도를 출력해주는 함수
	switch (imenu)
	{
	case MT_EASY:
		cout << "*************************** 쉬움 ***************************" << endl;
		break;
	case MT_NORMAL:
		cout << "*************************** 보통 ***************************" << endl;
		break;
	case MT_HARD:
		cout << "************************** 어려움 ***************************" << endl;
		break;
	}
}

void OPplayer(_tagPlayer *pPlayer) {
	// 플레이어 정보를 출력한다.
	cout << "================== Player ==================" << endl;
	cout << "이름 : " << pPlayer->strName << "\t직업 : " <<
		pPlayer->strJobName << endl;
	cout << "레벨 : " << pPlayer->iLevel << "\t경험치 : " <<
		pPlayer->iExp << " / " << iLevelUpExp[pPlayer->iLevel - 1] << endl;

	// 무기를 장착하고 있을 경우 공격력에 무기공격력을 추가하여 출력한다.
	if (pPlayer->bEquip[EQ_WEAPON] == true)
	{
		cout << "공격력 : " << pPlayer->iAttackMin << " + " <<
			pPlayer->tEquip[EQ_WEAPON].iMin << " - " <<
			pPlayer->iAttackMax << " + " << pPlayer->tEquip[EQ_WEAPON].iMax;
	}

	else
	{
		cout << "공격력 : " << pPlayer->iAttackMin << " - " <<
			pPlayer->iAttackMax;
	}

	// 방어구를 장착하고 있을 경우 방어력에 방어구 방어력을 추가하여 출력한다.
	if (pPlayer->bEquip[EQ_ARMOR] == true)
	{
		cout << "\t방어력 : " << pPlayer->iArmorMin << " + " <<
			pPlayer->tEquip[EQ_ARMOR].iMin << " - " <<
			pPlayer->iArmorMax << " + " << pPlayer->tEquip[EQ_ARMOR].iMax << endl;
	}

	else
	{
		cout << "\t방어력 : " << pPlayer->iArmorMin << " - " <<
			pPlayer->iArmorMax << endl;
	}

	cout << "체력 : " << pPlayer->iHP << " / " << pPlayer->iHPMax <<
		"\t마나 : " << pPlayer->iMP << " / " << pPlayer->iMPMax << endl;

	if (pPlayer->bEquip[EQ_WEAPON])
		cout << "장착무기 : " << pPlayer->tEquip[EQ_WEAPON].strName;

	else
		cout << "장착무기 : 없음";

	if (pPlayer->bEquip[EQ_ARMOR])
		cout << "\t장착방어구 : " << pPlayer->tEquip[EQ_ARMOR].strName << endl;

	else
		cout << "\t장착방어구 : 없음" << endl;

	cout << "보유골드 : " << pPlayer->tInventory.iGold << " Gold" << endl << endl;

}

void OPmonster(_tagMonster *pMonster) {
	// 몬스터 정보 출력
	cout << "================== Monster ==================" << endl;
	cout << "이름 : " << pMonster->strName << "\t레벨 : " <<
		pMonster->iLevel << endl;
	cout << "공격력 : " << pMonster->iAttackMin << " - " <<
		pMonster->iAttackMax << "\t방어력 : " << pMonster->iArmorMin <<
		" - " << pMonster->iArmorMax << endl;
	cout << "체력 : " << pMonster->iHP << " / " << pMonster->iHPMax <<
		"\t마나 : " << pMonster->iMP << " / " << pMonster->iMPMax << endl;
	cout << "획득경험치 : " << pMonster->iExp << "\t획득골드 : " <<
		pMonster->iGoldMin << " - " << pMonster->iGoldMax << endl << endl;
}

int BattleMenu() {
	cout << "1. 공격" << endl;
	cout << "2. 도망가기" << endl;
	cout << "메뉴를 선택하세요 : ";
	int imenu = Input();

	if (imenu == INT_MAX || imenu <= BATTLE_NONE || imenu > BATTLE_BACK)
		return BATTLE_NONE;

	return imenu;
}


//몬스터의 기본 데이터를 작성하기위한 함수
_tagMonster CreateMonster(char* pName, int iAttackMin, int iAttackMax, int iArmorMin, int iArmorMax,
	int iHP, int iMP, int iLevel,int iExp, int iGoldMin, int iGoldMax) {
	_tagMonster monster = {};

	strcpy_s(monster.strName, pName);
	monster.iAttackMin = iAttackMin;
	monster.iAttackMax = iAttackMax;
	monster.iArmorMin = iArmorMin;
	monster.iArmorMax = iArmorMax;
	monster.iHP = iHP;
	monster.iHPMax = iHP;
	monster.iMP = iMP;
	monster.iMPMax = iMP;
	monster.iLevel = iLevel;
	monster.iExp = iExp;
	monster.iGoldMin = iGoldMin;
	monster.iGoldMax = iGoldMax;

	return monster;
}

void setMonster(_tagMonster *pMonsterArr) { //몬스터 세팅함수
	pMonsterArr[0] = CreateMonster("난쟁이(하급 몬스터)", 20, 30, 2, 5, 100, 10, 1, 1000, 500, 1500);
	pMonsterArr[1] = CreateMonster("똥쟁이(몬스터)", 80, 130, 60, 90, 2000, 100, 5, 7000, 6000, 8000);
	pMonsterArr[2] = CreateMonster("방구쟁이(몬스터)", 250, 500, 200, 400, 30000, 20000, 10, 30000, 20000, 50000);
	
}

void Battle(_tagPlayer *pPlayer, _tagMonster *pMonster) {

	// 예를 들어 Min 5 Max 15 라고 가정할 경우 
	// 15 - 5 + 1 을 하면 11이 된다. 11로 나눈 나머지는 0 ~ 10이
	// 나오게 되고 여기에 Min값인 5를 더하게 되면
	// 5 ~ 15 사이로 값이 나오게 되는것이다.
	int	iAttackMin = pPlayer->iAttackMin;
	int	iAttackMax = pPlayer->iAttackMax;

	// 무기를 장착하고 있을 경우 무기와 Min, Max를 더해준다.
	if (pPlayer->bEquip[EQ_WEAPON])
	{
		iAttackMin += pPlayer->tEquip[EQ_WEAPON].iMin;
		iAttackMax += pPlayer->tEquip[EQ_WEAPON].iMax;
	}

	int	iAttack = rand() % (iAttackMax - iAttackMin + 1) +
		iAttackMin;
	int	iArmor = rand() % (pMonster->iArmorMax - pMonster->iArmorMin + 1) +
		pMonster->iArmorMin;

	int	iDamage = iAttack - iArmor;
	// 삼항연산자 : 조건식 ? true일때값 : false일때값;
	//if (iDamage < 1)
	//	iDamage = 1;
	iDamage = iDamage < 1 ? 1 : iDamage;

	// 몬스터 HP를 감소시킨다.
	pMonster->iHP -= iDamage;

	cout << pPlayer->strName << " 가 " << pMonster->strName <<
		"에게 " << iDamage << " 피해를 입혔습니다." << endl;

	// 몬스터가 죽었을 경우를 처리한다.
	if (pMonster->iHP <= 0)
	{
		cout << pMonster->strName << " 몬스터가 사망하였습니다." << endl;

		pPlayer->iExp += pMonster->iExp;
		int	iGold = (rand() % (pMonster->iGoldMax - pMonster->iGoldMin + 1) +
			pMonster->iGoldMin);
		pPlayer->tInventory.iGold += iGold;

		cout << pMonster->iExp << " 경험치를 획득하였습니다." << endl;
		cout << iGold << " Gold를 획득하였습니다." << endl;

		pMonster->iHP = pMonster->iHPMax;
		pMonster->iMP = pMonster->iMPMax;

		// 레벨업을 했는지 체크해본다.
		if (pPlayer->iExp >= iLevelUpExp[pPlayer->iLevel - 1])
		{
			// 플레이어 경험치를 레벨업에 필요한 경험치만큼 차감한다.
			pPlayer->iExp -= iLevelUpExp[pPlayer->iLevel - 1];

			// 레벨을 증가시킨다.
			++pPlayer->iLevel;

			cout << "레벨업 하였습니다." << endl;

			// 능력치를 상승시킨다.
			// 직업 인덱스를 구한다.
			int	iJobIndex = pPlayer->eJob - 1;
			int	iHPUp = rand() % (tLvUpTable[iJobIndex].iHPMax - tLvUpTable[iJobIndex].iHPMin + 1) +
				tLvUpTable[iJobIndex].iHPMin;
			int	iMPUp = rand() % (tLvUpTable[iJobIndex].iMPMax - tLvUpTable[iJobIndex].iMPMin + 1) +
				tLvUpTable[iJobIndex].iMPMin;

			pPlayer->iAttackMin += tLvUpTable[iJobIndex].iAttackMin;
			pPlayer->iAttackMax += tLvUpTable[iJobIndex].iAttackMax;
			pPlayer->iArmorMin += tLvUpTable[iJobIndex].iArmorMin;
			pPlayer->iArmorMax += tLvUpTable[iJobIndex].iArmorMax;

			pPlayer->iHPMax += iHPUp;
			pPlayer->iMPMax += iMPUp;

			// 체력과 마나를 회복시킨다.
			pPlayer->iHP = pPlayer->iHPMax;
			pPlayer->iMP = pPlayer->iMPMax;
		}
		return;
	}

	// 몬스터가 살아있다면 플레이어를 공격한다.
	iAttack = rand() % (pMonster->iAttackMax - pMonster->iAttackMin + 1) +
		pMonster->iAttackMin;

	int	iArmorMin = pPlayer->iArmorMin;
	int	iArmorMax = pPlayer->iArmorMax;

	if (pPlayer->bEquip[EQ_ARMOR])
	{
		iArmorMin += pPlayer->tEquip[EQ_ARMOR].iMin;
		iArmorMax += pPlayer->tEquip[EQ_ARMOR].iMax;
	}

	iArmor = rand() % (iArmorMax - iArmorMin + 1) +
		iArmorMin;

	iDamage = iAttack - iArmor;
	// 삼항연산자 : 조건식 ? true일때값 : false일때값;
	//if (iDamage < 1)
	//	iDamage = 1;
	iDamage = iDamage < 1 ? 1 : iDamage;

	// 플레이어의 HP를 감소시킨다.
	pPlayer->iHP -= iDamage;

	cout << pMonster->strName << " 가 " << pPlayer->strName <<
		"에게 " << iDamage << " 피해를 입혔습니다." << endl;

	// 플레이어가 죽었을 경우
	if (pPlayer->iHP <= 0)
	{
		cout << pPlayer->strName << " 플레이어가 사망하였습니다." << endl;

		int	iExp = pPlayer-> iExp * 0.1f;
		int	iGold = pPlayer->tInventory.iGold * 0.1f;

		pPlayer->iExp -= iExp;
		pPlayer->tInventory.iGold -= iGold;

		cout << iExp << " 경험치를 잃었습니다." << endl;
		cout << iGold << " Gold를 잃었습니다." << endl;

		// 플레이어의 HP와 MP를 회복한다.
		pPlayer->iHP = pPlayer->iHPMax;
		pPlayer->iMP = pPlayer->iMPMax;
	}
}


void runBattle(_tagPlayer *pPlayer, _tagMonster *pMonsterArr, int imenu) { //배틀을 위한 함수

	
	while (true) {
		system("cls");
		BattleMode(imenu);

		//플레이어를 출력
		OPplayer(pPlayer);

		OPmonster(&pMonsterArr[imenu -1]);

		switch (BattleMenu())
		{
		case BATTLE_ATTACK:
			Battle(pPlayer, &pMonsterArr[imenu - 1]);
			system("pause");
			break;
		case BATTLE_BACK:
			return;
		}
	}
}

//맵에 관련된 동작을 처리하는 함수
void runMap(_tagPlayer *pPlayer, _tagMonster *pMonsterArr) {
	bool Loop = true;// While문의 무한루프 처리를 위한 bool타입 변수
	while (Loop) {//true인 상태로 무한 루프를 돌게한다

		int imenu = OPMapMenu();

		if (MT_BACK == imenu)
			return;

		//전투를 시작한다

		runBattle(pPlayer, pMonsterArr, imenu);
	}
}

_tagLevelUpStatus CreateLupStatus(int iAttackMin , int iAttackMax, int iArmorMin, int iArmorMax,
	int iHPMin, int iHPMax, int iMPMin, int iMPMax) 
{
	_tagLevelUpStatus status = {};

	status.iAttackMin = iAttackMin;
	status.iAttackMax = iAttackMax;
	status.iArmorMin = iArmorMin;
	status.iArmorMax = iArmorMax;
	status.iHPMin = iHPMin;
	status.iHPMax = iHPMax;
	status.iMPMin = iMPMin;
	status.iMPMax = iMPMax;


	return status;
}

int OPstoreMenu() {
	while (true)
	{
		system("cls");
		cout << "*************************** 상점 ***************************" << endl;
		cout << "1. 무기상점" << endl;
		cout << "2. 방어구상점" << endl;
		cout << "3. 뒤로가기" << endl;
		cout << "상점을 선택하세요 : ";
		int imenu = Input();

		if (imenu == INT_MAX || imenu <= SM_NONE || imenu > SM_BACK)
			return SM_NONE;

		return imenu;
	}
}

int OPitemStorList(_tagInventory *pInventory, _tagItem *pStore, int iItemcount) {
	for (int i = 0; i <iItemcount; ++i)
	{
		cout << i + 1 << ". 이름 : " << pStore[i].strName <<
			"\t종류 : " << pStore[i].strTypeName << endl;
		cout << "공격력 : " << pStore[i].iMin << " - " <<
			pStore[i].iMax << endl;
		cout << "판매가격 : " << pStore[i].iPrice <<
			"\t구매가격 : " << pStore[i].iSell << endl;
		cout << "설명 : " << pStore[i].strDesc << endl << endl;
	}

	cout << iItemcount + 1 << ". 뒤로가기" << endl;
	cout << "보유금액 : " << pInventory->iGold << " Gold" << endl;
	cout << "남은공간 : " << INVENTORY_MAX - pInventory->iItemCount << endl;
	cout << "구입할 아이템을 선택하세요 : ";
	int imenu = Input();

	if (imenu <1 || imenu>iItemcount + 1)
		return INT_MAX;

}

void BuyItem(_tagInventory *pInventory, _tagItem *pStore,  int itemcount, int storeType) {
	while (true)
	{
		system("cls");
		switch (storeType)
		{
		case SM_WEAPON:
			cout << "*************************** 무기상점 ***************************" << endl;
			break;
		case SM_ARMOR:
			cout << "*************************** 방어구상점 ***************************" << endl;
			break;
		}
		int iInput = OPitemStorList(pInventory, pStore, itemcount);

		if (iInput == INT_MAX) {
			cout << "잘못 입력하였습니다" << endl;
			system("pause");
			continue;
		}

		else if (iInput == itemcount + 1)
			break;

		// 상점판매목록 배열의 인덱스를 구해준다.
		int	iIndex = iInput - 1;

		// 인벤토리가 꽉 찼는지 검사한다.
		if (pInventory->iItemCount == INVENTORY_MAX)
		{
			cout << "가방이 꽉 찼습니다." << endl;
			system("pause");
			continue;
		}

		// 돈이 부족할 경우
		else if (pInventory->iGold < pStore[iIndex].iPrice)
		{
			cout << "보유금액이 부족합니다." << endl;
			system("pause");
			continue;
		}

		// 처음에 iItemCount는 하나도 추가되어있지 않기 때문에 0으로 초기화
		// 되어 있으므로 0번 인덱스에 구매한 아이템을 추가하게 된다. 그리고
		// 카운트가 1이 된다. 다음번에 추가할때는 1번 인덱스에 추가하게된다.
		pInventory->tItem[pInventory->iItemCount] =
			pStore[iIndex];
		++pInventory->iItemCount;

		// 골드를 차감한다.
		pInventory->iGold -= pStore[iIndex].iPrice;

		cout << pStore[iIndex].strName << " 아이템을 구매하였습니다." << endl;
		system("pause");

	
	}
}

	void runStore(_tagInventory *pInverntory, _tagItem* pWeapon, _tagItem *pArmor) {
		while (true) {
			switch (OPstoreMenu())
			{
			case SM_WEAPON:
				BuyItem(pInverntory, pWeapon, STORE_WEAPON_MAX, SM_WEAPON);
				break;
			case SM_ARMOR:
				BuyItem(pInverntory, pArmor, STORE_ARMOR_MAX, SM_ARMOR);
				break;
			case SM_BACK:
				return;
			}
		}
	}

	_tagItem CreateItem(char* pName, ITEM_TYPE eType, int iMin, int iMax, int iPrice, int iSell,
		char* pDesc) {
	_tagItem item = {};

	strcpy_s(item.strName, pName);
	strcpy_s(item.strDesc, pDesc);

	item.eType = eType;

		switch (eType)
		{
		case IT_WEAPON:
			strcpy_s(item.strTypeName, "무기");
			break;
		case IT_ARMOR:
			strcpy_s(item.strTypeName, "방어구");
			break;
		}
		item.iMin = iMin;
		item.iMax = iMax;
		item.iPrice = iPrice;
		item.iSell = iSell;

		return item;
		
}

int main() {
	srand((unsigned int)time(0));
	bool Loop = true; // While문의 무한루프 처리를 위한 bool타입 변수

	_tagPlayer player = {};//게임 시작시 플레이어 정보를 설정

	SetPlayer(&player);//플레이어 세팅

	_tagMonster tMonsterArr[MT_BACK - 1] = {}; //몬스터 생성

	setMonster(tMonsterArr);

	tLvUpTable[JOB_KNIGHT - 1] = CreateLupStatus(4, 10, 8, 16, 50, 100, 10, 20);
	tLvUpTable[JOB_ARCHER - 1] = CreateLupStatus(10, 15, 5, 10, 30, 60, 30, 50);
	tLvUpTable[JOB_WIZARD - 1] = CreateLupStatus(15, 20, 3, 7, 20, 40, 50, 100);

	// 상점에서 판매할 아이템 목록을 생성한다.
	_tagItem	tStoreWeapon[STORE_WEAPON_MAX] = {};
	_tagItem	tStoreArmor[STORE_ARMOR_MAX] = {};

	tStoreWeapon[0] = CreateItem("목검", IT_WEAPON, 5, 10, 1000, 500, "누군가 쓰다버린 나무칼");
	tStoreWeapon[1] = CreateItem("한조의 활", IT_WEAPON, 20, 10, 7000, 3500, "류오- 와가테키오 쿠라에");
	tStoreWeapon[2] = CreateItem("마법사의 양말", IT_WEAPON, 90, 150, 30000, 15000, "된장냄새가난다");

	tStoreArmor[0] = CreateItem("팬티", IT_ARMOR, 2, 5, 1000, 500, "냄새는 나지만 방어력이 오를것같다");
	tStoreArmor[1] = CreateItem("소가죽 갑옷", IT_ARMOR, 10, 20, 7000, 3500, "소의고기는 누가 먹었을까?");
	tStoreArmor[2] = CreateItem("아이언맨 슈트", IT_ARMOR, 70, 90, 30000, 15000, "아주 단단하고 유명한 그옷");


	while (Loop) { //true인 상태로 무한 루프를 돌게한다
		switch (OPMainMenu())
		{
		case MM_MAP:
			runMap(&player, tMonsterArr); //맵관련 루프동작을 위한 함수호출
			break;
		case MM_STORE:
			runStore(&player.tInventory, tStoreWeapon, tStoreArmor);
			break;
		case MM_INVENTORY:
			break;
		case MM_EXIT:
			Loop = false; //MM_EXIT=나가기 를 선택한경우 Loop=false되어 while문 무한루프를 끝내게된다.
			break;
		}
	}
}