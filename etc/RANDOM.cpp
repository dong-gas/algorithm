// 난수 생성기 [0, 2^32-1]
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// 배열 무작위 정렬
shuffle(all(v), rng);

//rng()로 사용
cout<<rng();     //랜덤 정수 출력 (출력할 때마다 바뀜)
int x=rng()%100; //0~99 랜덤 정수
