#include <bits/extc++.h>
/*
bits/extc++.h 인식 못 하면... (ex. SCPC)
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
*/
using namespace __gnu_pbds;
template<class T> using PBDS = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<class T> using multiPBDS = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
PBDS<ll> s;

/*
pbds swap: O(1)아님.
small to large할 때 주의
*/

//s.order_of_key(x): x보다 작은(미만) 원소의 개수
//s.find_by_order(y): y번째(0-based) 원소가 있는 iterator 반환 (0-based다. 즉, s.find_by_order(5)는 6번째 원소 반환)


//multiPBDS 사용법
1. erase 직접 구현
void m_erase(multiPBDS<ll> &OS, ll val){
    ll index = OS.order_of_key(val);
    auto it = OS.find_by_order(index);
    if(*it == val) OS.erase(it);
}

2. find()할 때 원하는 값 안나옴.
  order_of_key로 더 작은 거 개수 세고, find_by_order로 그 위치 알아내서 일치하는지 비교하는 식으로 하자.
