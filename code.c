#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define MAPSIZE 20
#define MCOUNT 28
int usermapping( char* username,int(*usermovement)[2],int* turnptr);
int shfunction(char(*monster)[10],int(*usermovement)[2],float monster_hp,int(*monget)[20],float bokki_hp,int boki);
void monsterget(int(*monget)[20]);
int main(void){
    //몬스터 행동전투 공격 아이템 도망
    srand((unsigned int)time(NULL)); //seed값으로 현재시간 부여 
// 전투 승리후 체력을 회복한다. 전투승리후 전체체력통이 증가한다.
// 전체 체력통(max_hp)가 있어야 체력회복하고 체력통을 증가 시킬 수 있음

    float user_hp = 3000;
    float user_maxhp = 3000 ; 
    int choice = 0 ;
    int turn = 1 ;
    int* turnptr=&turn; 
    float monster_hp = user_hp*(rand() % 30 + 10) * 0.1; //현재 유저체력의1~3배
    float monster_attack = user_maxhp*(rand() % 25 + 6) * 0.1; //현재 유저 전체 체력의 0.5~3.0배
    float user_attack = (user_hp*0.5)*(rand() % 5 + 1); // 현재 체력의 
    float bokki_hp = user_hp*(rand() % 30 + 51) * 0.1; // 전체체력의 5~8배
    float potion = user_hp*(rand() % 8 + 4) * 0.1; //전체체력의 0.3 ~0.8배 회복
    float victory_hp = user_hp*(rand() % 10 + 1 +3) * 0.1;//전투후 0.3~1.0배 회복  
    // float max_hp = user_hp*(rand() % 26 + 13) * 0.1; // 전투 후 체력 재산정 max_hp
    float run = (rand() % 10 + 1) * 0.1;
    int item_choice = 0;
    int item_guard = 0;
    int bokkicalibur = 0;
    int usermovement[1][2]={{10,10}};
    int monstercreating[20][20];
    int item_possibility = rand() % 100 +1;
    int revival=0;
    int item_potion=3;

    
//박선생 part
    char user_name[30];
    printf("유저이름을 입력하세요\n");
    scanf("%s",user_name);
    srand(time(NULL));
    int meet_x,meet_y, count,up_mhp,up_bmhp;
    int boki =0;
    int i=0;
    char monster[28][10]=
    {
        "강진영", "권철민","김 건", "김민아","김성근","김승수","김영곤","김재신","김혜빈","노주영",
        "박민건","박선후","박장미","박희정","서 훈","안광민","오은지","유시온","이동준","이은승",
        "이준호","이 철","임석현","조대정","조세빈","황운하","황은비","보키몬"
    };
    // char mon[2][2]=monster[i],monster[27];
    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            monstercreating[i][j]=0;
        }
        
    }
        while(1){
    monsterget(monstercreating);
    usermapping(user_name,usermovement,turnptr);
    
    while((boki=shfunction(monster,usermovement,monster_hp,monstercreating,bokki_hp,boki)) == 0)
                usermapping(user_name,usermovement,turnptr);

    // 아이템 얻기
    printf("%d턴\n",turn);
    if (turn % 3 == 0){
        printf("아이템 주사위는 %d입니다.\n",item_possibility);
        // item_possibility = (rand() % 6 + 1);
        if(item_possibility<5){ // 방패 얻기
            item_guard += 1;
            printf("현재 방패의 개수 : %d\n", item_guard);
        turn += 1;
    }
    }
    else if (turn % 3 == 0)
    {
        // item_possibility = (rand() % 6 + 1);
        int item_possibility = rand() % 100 +1;
        printf("아이템 주사위는 %d입니다.\n",item_possibility);
        if(item_possibility<5){ //  보키칼리버얻기
            bokkicalibur += 1; 
            printf("현재 보키칼리버 개수 : %d", bokkicalibur);
        turn += 1;
    }
    }
    else if (turn % 3 == 0)
    {
        // item_possibility = (rand() % 6 + 1);
        int item_possibility = rand() % 100 +1;
        printf("아이템 주사위는 %d입니다.\n",item_possibility);
        if(item_possibility<5){ //  부활 얻기
            revival += 1; 
            printf("현재 파워엘릭서 개수 : %d\n", revival);
        turn += 1;
    }
    else if(item_possibility >= 5 && item_possibility <15){
        item_potion += 1;
    }
    }
    
    //전투시작
    while(boki == 3){
    //전투시작 -> 공격,아이템,도망 선택하기
   

    printf("\n1:전투 2:아이템 3:도망\n행동을 입력하세여\n");
    scanf("%d", &choice);
    if ( choice == 1){
        printf("%d번째 턴입니다.\n",turn);
    //전투
    //유저의 공격
    monster_hp = monster_hp - user_attack; 
    printf("\n&&&&&&&&&전투 시작&&&&&&&&&&&\n");
    printf("-----------------------------------유저의 턴------------------------------------\n");

    printf("현재 몬스터 hp : %.0f\n유저의 공격 : %.0f\n",monster_hp,user_attack);
    user_attack = (user_hp*0.5)*(rand() % 5 + 1); // 다음공격 위해서 유저 공격력 재설정

        
        if(monster_hp >0){
        user_hp = user_hp - monster_attack;
        printf("----------------------------------몬스터의 턴---------------------------------\n");

        printf("몬스터의 공격 : %.0f\n현재 유저 체력 : %.0f\n",monster_attack,user_hp);
        monster_attack = user_maxhp*(rand() % 25 + 6) * 0.1; //다음 공격을 위해서 몬스터 공격력 재설정
            if(user_hp >0){ //공격받고 살아있으면 다시 행동시작
            turn +=1;
            monster_hp=user_maxhp*(rand() % 30 + 10) * 0.1;

            continue;
            }else
            printf("Lose 망했어요 ㅠㅠ\n"); //패배
            user_hp = user_maxhp;
            monster_hp=user_maxhp*(rand() % 30 + 10) * 0.1;
            break;
        }else{
            //승리 메세지 출력 현재 hp출력 후 행동 종료
            printf("***********************************Victory**********************************\n승리후 남은hp: %.0f\n", user_hp);
            //승리후 hp통 증가
            user_maxhp = user_maxhp *(rand() % 26 + 13) * 0.1 ;
            //승리후 hp 회복
            user_hp = user_hp + user_maxhp * ((rand() % 11 + 3) * 0.1); 
            if(user_hp >user_maxhp)
                user_hp =user_maxhp;
            printf("전투후\n현재 HP%.0f\n",user_hp);
            monster_hp = user_hp*(rand() % 30 + 10) * 0.1;
            break;
        }

    //몬스터의 공격
    user_hp = user_hp - monster_attack;
    printf("유저 체력%.0f\n몬스터의 공격 %.0f\n", user_hp,monster_attack);
    monster_attack = user_maxhp*(rand() % 25 + 6) * 0.1; //다음 공격을 위해서 몬스터 공격력 재설정
        if(user_hp >0){
        turn +=1;
        continue;
        }else
        printf("Lose 망했어요 ㅠㅠ\n"); //패배
        user_hp = user_maxhp;
        break;
        }
    else if( choice == 2){
        //아이템
        //포션
    printf("-----------------------------------유저의 턴------------------------------------\n");
        printf("\n아이템을 선택해주세요\n 1.포션 2.복이칼리버 3.방패 4.파워엘릭서\n ");
        scanf("%d", &item_choice);
        if (item_choice ==1 ){
            //포션
        item_potion -= 1;
        printf("포션을 사용합니다. 남은 포션개수:%.0d\n", item_potion);
        user_hp = user_hp +potion;
        if(user_hp >user_maxhp)
                user_hp =user_maxhp;
        turn +=1;
        printf("현재HP:%.0f", user_hp);
        continue;
        }else if(item_choice ==2){ //복이칼리버
            // bokki_hp = 0;
            if (bokkicalibur > 0){
                printf("복이가 아니라서 아이템이 없어집니다.\n"); 
                bokkicalibur -= 1;
                turn++;
                continue;
            }
                else{
                printf("아이템이 없습니다.\n");
                turn++;
                continue;
                }
        }else if(item_choice ==3){ // 방패
            if(item_guard>0)
            {
                printf("방패 아이템을 사용합니다 남은 개수%d\n한 번 적의 공격을 절반으로 만듭니다.\n",item_guard);
                monster_attack = monster_attack*0.5;
                item_guard -= 1;
                printf("방패개수 %d",item_guard);
            }
            else
            {
                printf("아이템이 없습니다\n");
            }
            if (item_guard >10){
                    item_guard =10;
                    turn++;
            continue;
            }
        }

            
        if(item_choice ==4){ // 부활
            if(revival>0)
            {
            printf("파워엘릭서 아이템을 사용합니다 남은 개수%d.\n",revival);
            user_hp=user_maxhp;
            printf("유저체력 %.0f\n",user_hp);
            revival -= 1;
            printf("파워엘릭서 개수 %d\n",revival);
            }
            else{
            printf("아이템이 없습니다.\n");
            turn++;
            }
            if (revival >10){
                    revival =10;
                    turn++;
            continue;
            }

        }
    
        //아이템 사용 끝나고 몬스터의 공격 
            user_hp = user_hp - monster_attack;
    printf("-----------------------------------몬스터의 턴------------------------------------\n");

            printf("몬스터의 공격%.0f\n유저의 체력 %.0f\n", monster_attack,user_hp);
            monster_attack = user_maxhp*(rand() % 25 + 6) * 0.1; //다음 공격을 위해서 몬스터 공격력 재설정
            if(user_hp >0){
            turn +=1;
            continue;
            }else
            printf("ㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠLose 망했어요 ㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠ\n"); //패배
        user_hp = user_maxhp;

            break;
    }

    else if(choice == 3 ){
        //도망
        if (run > 0.3){ //도망 실패
    printf("-----------------------------------유저의 턴------------------------------------\n");

        printf("Run 실패 !!\n٩(´Д` ;)۶:.*\n");
        run = (rand() % 10 + 1) * 0.1; //도망 확률 재설정
        // 도망 실패 후 맞기 
            user_hp = user_hp - monster_attack;
    printf("-----------------------------------몬스터의 턴------------------------------------\n");

            printf("유저 체력%.0f\n몬스터의 공격 %.0f\n", user_hp,monster_attack);
            monster_attack = user_maxhp*(rand() % 25 + 6) * 0.1; //다음 공격을 위해서 몬스터 공격력 재설정
            if(user_hp >0){
            turn +=1;
            continue;
            }else
            printf("***************************Lose 망했어요 ㅠㅠ*****************************\n"); //패배
        user_hp = user_maxhp;

            break;
        }else //도망성공
        printf("Run 성공 기모띠\nദ്ദി◍•ᴗ•◍)\n");
        run = (rand() % 10 + 1) * 0.1;//도망 확률 재설정
        break; // 다시 돌아가기
    }//else // 1,2,3 외에 다른 입력했을 때
    //printf("잘못된 입력입니다. 다시 입력해주세요\n");
    //continue;

                                                        }

//복기 만나기



    while(boki == 1){
        //복기복기복기복기복기복기복기복기복기복기복기복기복기복기복기복기ㅍ
    //전투시작 -> 공격,아이템,도망 선택하기
    printf("--------------------------------------------유저의 턴---------------------------------------------\n");
    printf("1:전투 2:아이템 3:도망\n입력하세여");
    scanf("%d", &choice);
    if ( choice == 1){
        printf("\n%d번째 턴입니다.\n",turn);
    //전투
    //유저의 공격
    bokki_hp = bokki_hp - user_attack;
    printf("bokki hp%.0f\n 유저의 공격%.0f\n",bokki_hp,user_attack);

    user_attack = (user_hp*0.5)*(rand() % 5 + 1) ; // 다음공격 위해서 유저 공격력 재설정

        if(bokki_hp >0){
               user_hp = user_hp - monster_attack;
        printf("---------------------------------------------bokimon 턴----------------------------------------------\n");
        printf("유저 체력%.0f\n 몬스터의 공격 %.0f", user_hp,monster_attack);
        monster_attack = user_maxhp*(rand() % 25 + 6) * 0.1; //다음 공격을 위해서 몬스터 공격력 재설정
            continue;
        }else{
            //승리 메세지 출력 현재 hp출력 후 행동 종료
            printf("******Victory*******\n 현재hp: %.0f\n", user_hp);
            //승리후 hp통 증가
            user_maxhp = user_hp *(rand() % 26 + 13) * 0.1 ;
            
            
            //승리후 hp 회복
            user_hp = user_hp + user_maxhp * ((rand() % 11 + 3) * 0.1); 
            if(user_hp >user_maxhp)
                user_hp =user_maxhp;

        }

        if(user_hp <=0){
            printf("       ---------------------\n");
            printf("            BAD ENDING\n");
            printf("       ---------------------\n");
            printf("  ⣿⣿⣿⣿⣿⣿⣿⡿⠛⠉⠉⠉⠉⠛⠻⣿⣿⠿⠛⠛⠙⠛⠻⣿⣿⣿⣿⣿⣿⣿\n");
            printf("  ⣿⣿⣿⣿⣿⠟⠁⠀⠀⠀⢀⣀⣀⡀⠀⠈⢄⠀⠀⠀⠀⠀⠀⠀⢻⣿⣿⣿⣿⣿\n");
            printf("  ⣿⣿⣿⣿⠏⠀⠀⠀⠔⠉⠁⠀⠀⠈⠉⠓⢼⡤⠔⠒⠀⠐⠒⠢⠌⠿⢿⣿⣿⣿\n");
            printf("  ⣿⣿⣿⡏⠀⠀⠀⠀⠀⠀⢀⠤⣒⠶⠤⠭⠭⢝⡢⣄⢤⣄⣒⡶⠶⣶⣢⡝⢿⣿\n");
            printf("  ⡿⠋⠁⠀⠀⠀⠀⣀⠲⠮⢕⣽⠖⢩⠉⠙⣷⣶⣮⡍⢉⣴⠆⣭⢉⠑⣶⣮⣅⢻\n");
            printf("  ⠀⠀⠀⠀⠀⠀⠀⠉⠒⠒⠻⣿⣄⠤⠘⢃⣿⣿⡿⠫⣿⣿⣄⠤⠘⢃⣿⣿⠿⣿\n");
            printf("  ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠓⠤⠭⣥⣀⣉⡩⡥⠴⠃⠀⠈⠉⠁⠈⠉⠁⣴⣾⣿\n");
            printf("  ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠤⠔⠊⠀⠀⠀⠓⠲⡤⠤⠖⠐⢿⣿⣿⣿\n");
            printf("  ⠀⠀⠀⠀⠀⠀⠀⠀⣠⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣿⣿\n");
            printf("  ⠀⠀⠀⠀⠀⠀⠀⢸⣿⡻⢷⣤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣘⣿⣿\n");
            printf("  ⠀⠀⠀⠀⠀⠠⡀⠀⠙⢿⣷⣽⣽⣛⣟⣻⠷⠶⢶⣦⣤⣤⣤⣤⣶⠾⠟⣯⣿⣿\n");
            printf("  ⠀⠀⠀⠀⠀⠀⠉⠂⠀⠀⠀⠈⠉⠙⠛⠻⠿⠿⠿⠿⠶⠶⠶⠶⠾⣿⣟⣿⣿⣿\n");
            printf("  ⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⣿⣿⣿⣿⣿\n");
            printf("  ⣿⣿⣶⣤⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣤⣟⢿⣿⣿⣿⣿⣿⣿⣿\n");
            printf("  ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣶⣶⣶⣶⣶⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"); //패배
        user_hp = user_maxhp;
            continue;
        }
    else if(bokki_hp<=0)
    {
     printf("\n"
        "⠀⠀⠀⠆⡠⠰⠐⠒⠒⠒⠂⠆⣤⢀⠀⠀⢀⠀⠀⡀⠀⣀⣆⡀⠀⡀⠀⠀⠀⠀⢀⢀⠄⠆⠒⠒⠒⠒⠰⠠⡀⡀⠀⠀⡀⠀⢀⠀⠀⠀\n"
        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⢠⠀⠒⠂⠀⠀⠘⠛⠀⠀⠐⠒⠀⣠⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⡄⠀⠒⠀⠀⠀⠀\n"
        "                                                                            \n"   
        "⠀⠀⠀⠀⢠⡶⠶⠶⡆⠀⠀⢐⠶⠶⢖⡶⠶⠶⠶⠶⠶⠶⠶⠶⢖⠶⠶⠶⠶⠶⠶⡲⠶⠶⠶⠶⠶⢖⠶⠶⠶⡆⠀⠀⣶⠶⠶⢶⠀⠀⠀\n"
        "⠀⠀⠀⠀⠈⠁⠀⠀⠃⠀⠀⠈⠀⠀⠈⠁⠀⠀⠀⠀⠀⠀⠀⠀⠘⠀⠀⠀⠀⠀⠀⠃⠀⠀⠀⠀⠀⠈⠀⠀⠀⠃⠀⠀⠉⠀⠀⠘⠀⠀⠀\n"
        "⠀⠀⠀⠀⢰⡆⠀⠀⣆⣀⣀⣰⠀⠀⢰⡆⢀⣀⣀⣀⣀⣀⣀⠀⢰⠀⢀⣀⣀⡀⠀⡆⠀⣀⣀⣀⠀⢰⠀⠀⠀⣆⣀⣀⣶⠀⠀⢰⠀⠀⠠\n"
        "⠀⠀⠀⠀⠸⠇⠀⠀⠉⠉⠉⠉⠀⠀⠸⠇⠈⠉⠉⠉⠉⠉⠉⠀⠸⠀⠈⠉⠉⠁⠀⠇⠀⠉⠉⠉⠀⠸⠀⠀⠀⠉⠉⠉⠉⠀⠀⠸⠀⠀⠀\n"
        "⠀⠀⠀⠀⢠⡄⠀⠀⠀⠀⠀⠀⠀⠀⢠⡄⠀⠀⠀⠀⠀⠀⠀⠀⢠⠀⠀⠀⠀⠀⠀⡄⠀⠀⠀⠀⠀⢠⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠀⠀⠀\n"
        "⠀⠀⠀⠀⢸⡇⠀⠀⡟⠛⠛⢻⠀⠀⢸⡇⠀⠀⡟⠛⠛⣿⠀⠀⢸⠀⠀⢸⡟⠛⠛⡇⠀⠀⣾⠛⠛⠛⠛⠛⠛⡇⠀⠀⣿⠛⠛⠛⠀⠀⠀\n"
        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⡀⠀⠀\n"
        "⠀⠀⠀⠀⠸⣧⣤⣤⡇⠀⠀⢸⣤⣤⣜⣧⣤⣤⡇⠀⠀⣿⣤⣤⣜⣤⣤⣼⡇⠀⠀⣧⣤⣤⣿⠀⢠⣤⣤⡄⠀⣧⣤⣤⡿⠀⠀⢻⠟⠈⣶\n"
        "                                                                             \n"
        "⠀⠀⠀⠀⢀⡐⠂⠀⠀⠒⢀⠀⠀⠀⢀⠔⢄⠀⠀⠀⢀⠐⠂⠀⠂⠒⣀⠀⠀⠀⡄⣤⣴⠀⡄⠄⣤⣴⠄⠀⠀⢴⣤⡄⠀⠀⠀⠀⠀⠀⠀\n"
        "⠀⠀⠀⠐⠀⠀⠀⠀⠀⠀⠀⠐⠐⠠⠀⠙⠁⠀⠠⠐⠀⠀⠀⠀⠀⠀⠀⠐⠘⠐⠁⠈⠁⠐⠑⠂⠀⠁⠀⠃⠂⠀⠉⠀⠀⠀⠀⠀⠀⠀⠀\n"                                               
    );
    return 0;
    }
    


    }else if( choice == 2){
        //아이템
        //포션
        printf("\n아이템을 선택해주세요\n 1.포션 2.복이칼리버 3.방패 4.부활\n ");
        scanf("%d", &item_choice);
        if (item_choice ==1 ){
            //포션
        item_potion -= 1;
        printf("포션을 사용합니다. 남은 포션개수:%.0d\n", item_potion);
        user_hp = user_hp *(rand() % 8 + 3)* 0.1;
        if(user_hp >user_maxhp)
                user_hp =user_maxhp;
        turn +=1;
        printf("현재HP:%.0f\n", user_hp);
        continue;
        }else if(item_choice ==2){ //복이칼리버
            // bokki_hp = 0;
            if (bokkicalibur > 0){
                printf("보키컷\n"); 
                bokki_hp=0;
                bokkicalibur -= 1;
                turn++;
                continue;
            }
                else{
                printf("아이템이 없습니다.\n");
                turn++;
                continue;
                }
        }else if(item_choice ==3){ // 방패
            if(item_guard>0)
            {
                printf("방패 아이템을 사용합니다 남은 개수%d\n한 번 적의 공격을 절반으로 만듭니다.\n",item_guard);
                monster_attack = monster_attack*0.5;
                item_guard -= 1;
                printf("방패개수 %d",item_guard);
            }
            else
            {
                printf("\n아이템이 없습니다\n");
            }
            if (item_guard >10){
                    item_guard =10;
                    turn++;
            continue;
            }
        }

    }else if(choice == 3 ){
        //도망
        if (run > 0.3){ //도망 실패
        printf("Run 실패 안광민띠!!\n٩(´Д` ;)۶:.*\n");
        run = (rand() % 10 + 1) * 0.1; //도망 확률 재설정
        continue;
        }else //도망성공
        printf("Run 성공 기모띠\nദ്ദി◍•ᴗ•◍)\n");
        run = (rand() % 10 + 1) * 0.1;//도망 확률 재설정
        break; // 다시 돌아가기
    }else // 1,2,3 외에 다른 입력했을 때
    printf("잘못된 입력입니다. 다시 입력해주세요\n");

}
}
    return 0;
}

int usermapping( char* username,int(*usermovement)[2],int* turnptr)

{
if((usermovement[0][0]<0 || usermovement[0][0]>20) || (usermovement[0][1]<0 || usermovement[0][1]>20) ){
    printf("유저의 위치를 수정해야 합니다.\n");
    return -1;
}
char map[MAPSIZE][MAPSIZE];
int movement=0;
for (int i = 0; i < MAPSIZE; i++)
{
    for (int j = 0; j < MAPSIZE; j++)
    {
        map[i][j]='x'; 
    }
    
}

char userchoice[10];
while (movement==0)
{
printf ("%s가(이) 움직이고 싶은 방향을 골라주세요\n",username);
printf("ex)위 오른쪽 왼쪽 아래\n");
scanf("%s",userchoice);
//왼쪽 -103 //오른쪽 -104 //위 -100 //아래 -107

switch (userchoice[1])
{
    case -103://왼쪽
    usermovement[0][1]=usermovement[0][1]-1;
    printf("왼쪽 방향으로 캐릭터가 한칸 움직입니다.\n");
    if(usermovement[0][1]<=-1){
        usermovement[0][1]=0;
        printf("왼쪽 끝입니다.다른 방향으로 입력해주세요.\n");
        break;
    }
    movement++;
    break;
case -104://오른쪽
    usermovement[0][1]=usermovement[0][1]+1;
    printf("오른쪽 방향으로 캐릭터가 한칸 움직입니다.\n");
    if(usermovement[0][1]>=20){
        usermovement[0][1]=19;
        printf("오른쪽 끝입니다.다른 방향으로 입력해주세요.\n");
        break;
    }
    movement++;
    break;
case -100://위
    usermovement[0][0]=usermovement[0][0]-1;
    printf("위 방향으로 캐릭터가 한칸 움직입니다.\n");
       if(usermovement[0][0]<=-1){
        usermovement[0][0]=0;

        printf("위쪽 끝입니다.다른 방향으로 입력해주세요.\n");
        break;
    }
    movement++;
    break;
case -107://아래
    usermovement[0][0]=usermovement[0][0]+1;
    printf("아래 방향으로 캐릭터가 한칸 움직입니다.\n");
       if(usermovement[0][0]>=20){
         usermovement[0][0]=19;
        printf("아래쪽 끝입니다.다른 방향으로 입력해주세요.\n");
        break;
    }
    movement++;
    break;
default://디폴트
    printf("다시 입력해주세요\n");
    break;
}
}
printf("유저의 현재 위치\n");
map[usermovement[0][0]][usermovement[0][1]]='0';
printf("     ");
for (int i = 0; i < 20; i++)
{
    printf("%5d열",i);
}
printf("\n");


for (int i = 0; i < MAPSIZE; i++)
{
    printf("%3d행",i);
    for (int j = 0; j < MAPSIZE; j++)
    {
        printf("%7c",map[i][j]);
    
    }
    printf("\n\n");
}
printf("플레이어는 현재 %d열 %d행에 있습니다.\n",usermovement[0][1],usermovement[0][0]);

*turnptr+=1;
return 0;
}

int shfunction(char(*monster)[10],int(*usermovement)[2],float monster_hp,int(*monget)[20],float bokki_hp,int boki){
        srand(time(NULL));
        int count=rand()%29;
       int a,b;
        
        /*
        카운트=27
        i=0~27
        27번째의 if
        */
        if (monget[usermovement[0][1]][usermovement[0][1]]==1)//x열과 y열 이 유저위치와 일치할 때
        {
            for (int i= 0;i<MCOUNT-1;i++){ //28이 될때까지
                if ((a=strcmp(monster[i],monster[count]))==0)//비교한다 monster[i]와 monster[27]-->보키몬 비교
                {
                    monster_hp; //보키몬이 아니면 몬스터의 체력은 유저체력 * 일반몬스터 체력 상승                                                   
                    boki=3;    
                    printf("%s가 출현했다. %s의 HP=%.0f\n",monster[count],monster[count],monster_hp);
                    printf(
                            "⠀⠀⢙⣿⡛⣻⡛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠁⠀⠀⠀⢠⡀⠀⠀⢀⣄\n"
                            "⠀⠀⠈⠛⠉⠛⠁⠀⣀⣤⣄⣤⣴⣶⣶⣤⡀⠀⠀⠀⠀⣾⣷⡀⠀⠘⠋⠀\n"
                            "⠀⠀⠀⠀⠀⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⡎⠀⠀⠀⢹⣿⣧⠀⠀⠀⠀⠀⠀\n"
                            "⠀⠀⠀⠀⠀⠰⠛⣋⠉⠛⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠈⣿⣿⠀⠀⠀⠀⠀⠀\n"
                            "⠀⠀⠀⠀⣠⣶⣿⣿⣧⣀⣹⡼⣻⣿⣿⣿⣿⣤⡀⠀⠀⠀⢹⣿⡆⠀⠀⠀⠀⠀\n"
                            "⠀⠀⠀⣰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⡀⠀⠈⣿⣇⠀⠀⠀⠀⠀\n"
                            "⠀⠀⢰⣿⣿⣿⣿⣿⠿⠋⠁⣾⣿⣿⣿⣿⡟⠉⠙⠻⣿⣷⣿⣽⣿⣀⣤⡄⠀⠀\n"
                            "⠀⠀⣾⣿⣿⣿⡟⠁⠀⠀⢀⣿⣿⣿⣿⣟⠀⠀⠀⠀⠘⠻⣿⣿⣿⡿⠋⠀⠀⠀\n"
                            "⠀⠀⣿⣿⠟⠁⠀⠀⠀⢠⣿⣿⣿⣿⣿⣿⣷⡄⠀⠀⠀⠀⠀⠉⢻⡇⠀⠀⠀⠀\n"
                            "⠀⠀⠉⠀⠀⠀⠀⠀⢀⣾⣿⣿⠿⠿⠿⢿⣿⣿⡄⠀⠀⠀⠀⠀⠈⠃⠀⠀⠀⠀\n"
                            "⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣇⠀⠀⠀⠀⠙⠿⣿⣿⣶⣆⠀⠀⠀⠀⠀⠀⠀⠀\n"
                            "⠀⠀⠀⠀⠀⠀⠀⠀⠹⣿⣿⣯⠀⠀⠀⠀⠀⠀⠻⣿⣿⣿⣦⠀⠀⠀⠀⠀⠀⠀\n"
                            "⠀⠀⠀⠀⠀⠀⠀⠀⣀⣽⣿⣿⠀⠀⠀⠀⠀⠀⠀⠈⢿⣿⣿⡄⠀⠀⠀⠀⠀⠀\n"
                            "⠀⠀⠠⣤⣤⠀⠀⠸⠿⠿⠿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣿⣿⡆⠸⡷⠀⠀\n");
                }
                else if((b=strcmp(monster[count],"보키몬" ))==0 && i==1)
                {
                   bokki_hp;//보키몬이면 몬스터의 체력은 유저체력* 보스몬스터 체력 상슬률
                    printf("%s이 출현했다. %s의 HP=%.0f\n",monster[count],monster[count],bokki_hp);
                    
                      printf(
                            "⠀⠀⢙⣿⡛⣻⡛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠁⠀⠀⠀⢠⡀⠀⠀⢀⣄\n"
                            "⠀⠀⠈⠛⠉⠛⠁⠀⣀⣤⣄⣤⣴⣶⣶⣤⡀⠀⠀⠀⠀⣾⣷⡀⠀⠘⠋⠀\n"
                            "⠀⠀⠀⠀⠀⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⡎⠀⠀⠀⢹⣿⣧⠀⠀⠀⠀⠀⠀\n"
                            "⠀⠀⠀⠀⠀⠰⠛⣋⠉⠛⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠈⣿⣿⠀⠀⠀⠀⠀⠀\n"
                            "⠀⠀⠀⠀⣠⣶⣿⣿⣧⣀⣹⡼⣻⣿⣿⣿⣿⣤⡀⠀⠀⠀⢹⣿⡆⠀⠀⠀⠀⠀\n"
                            "⠀⠀⠀⣰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⡀⠀⠈⣿⣇⠀⠀⠀⠀⠀\n"
                            "⠀⠀⢰⣿⣿⣿⣿⣿⠿⠋⠁⣾⣿⣿⣿⣿⡟⠉⠙⠻⣿⣷⣿⣽⣿⣀⣤⡄⠀⠀\n"
                            "⠀⠀⣾⣿⣿⣿⡟⠁⠀⠀⢀⣿⣿⣿⣿⣟⠀⠀⠀⠀⠘⠻⣿⣿⣿⡿⠋⠀⠀⠀\n"
                            "⠀⠀⣿⣿⠟⠁⠀⠀⠀⢠⣿⣿⣿⣿⣿⣿⣷⡄⠀⠀⠀⠀⠀⠉⢻⡇⠀⠀⠀⠀\n"
                            "⠀⠀⠉⠀⠀⠀⠀⠀⢀⣾⣿⣿⠿⠿⠿⢿⣿⣿⡄⠀⠀⠀⠀⠀⠈⠃⠀⠀⠀⠀\n"
                            "⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣇⠀⠀⠀⠀⠙⠿⣿⣿⣶⣆⠀⠀⠀⠀⠀⠀⠀⠀\n"
                            "⠀⠀⠀⠀⠀⠀⠀⠀⠹⣿⣿⣯⠀⠀⠀⠀⠀⠀⠻⣿⣿⣿⣦⠀⠀⠀⠀⠀⠀⠀\n"
                            "⠀⠀⠀⠀⠀⠀⠀⠀⣀⣽⣿⣿⠀⠀⠀⠀⠀⠀⠀⠈⢿⣿⣿⡄⠀⠀⠀⠀⠀⠀\n"
                            "⠀⠀⠠⣤⣤⠀⠀⠸⠿⠿⠿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣿⣿⡆⠸⡷⠀⠀\n");

                    printf("\n");
                    printf(
                            "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡾\n"
                            "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⣰⢺⣿⣷⣬⠃⠀⠄\n"
                            "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⡇⣿⢸⣿⣿⣿⣆⡾⠀\n"
                            "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡻⣴⣴⣾⣿⣿⣿⠃⠀⠀⠀\n"
                            "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⡿⢾⡿⢿⣿⣿⣿⣆⠀⠀⠀⠀⠀\n"
                            "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣿⣿⠃⢸⠁⠸⣿⣿⣿⣿⣦⡀⠀⠀⠀\n"
                            "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣾⣿⡿⠁⠀⡿⠀⠀⢻⣿⣿⣿⣿⣷⣄⠀⠀⠀⠀\n"
                            "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⣿⣿⡿⠁⠀⢠⡇⠀⠀⠀⢿⣿⣿⣿⣿⣿⣦⠀⠀⠀⠀⠀\n"
                            "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣴⣿⣿⣿⠁⠀⠀⢸⡇⠀⠀⠀⠈⢻⣿⣿⣿⣿⣿⣧⡀⠀⠀⠀⠀⠀\n"
                            "⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⣿⠟⣿⡃⡄⠀⣸⡇⠀⢀⣀⣶⣿⣿⣿⣿⢿⣿⣿⣷⡀⠀⠀⠀⠀⠀⠀\n"
                            "⠀⠀⠀⠀⠀⠀⠀⠀⣰⣿⡿⠋⠀⣿⣿⣶⢤⣿⡇⡤⣮⣽⣿⣿⣿⣿⣿⡇⠙⣿⣿⣧⠀⠀⠀⠀⠀⠀⠀⠀\n"
                            "⠀⠀⠀⠀⠀⠀⠀⣰⣿⣿⠧⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⢈⣿⣿⣇⠀⠀⠀⠀⠀⠀⠀\n"
                            "⠀⠀⠀⠀⠀⠀⢀⠟⠁⠀⠀⠀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠀⠀⠀⠚⠻⣿⡀⠀⠀⠀⠀⠀⠀\n"
                            "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣿⣿⡏⠀⠀⠘⣿⣿⣿⣿⠁⠀⠀⠀⠀⠀⠈⠃⠀⠀⠀⠀⠀⠀\n"
                            "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢿⣿⣿⢇⠀⠀⠀⢸⣿⣿⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                            "           ⠠⠶⠴⠪⠷⠿⠛⠃   ⢨⢦⣨⢦        boki    \n");

                                                                                                            
                    boki=1;
                }
            }
                
        }
    
    
    return boki;
}

void monsterget(int(*monget)[20])
{
    
    for (int i = 0; i < 20; i++)
    {
        int random=rand()%10;
        for (int j = 0; j < 20; j++)
        {
                if(random>=1)
                {
                    monget[i][j]=1;
                }         
        }   
    }
}
