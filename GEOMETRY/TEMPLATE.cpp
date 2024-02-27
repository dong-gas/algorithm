struct pt{    
    ll x, y;
    pt() {x=0;y=0;}
    pt(ll p, ll q) {x=p, y=q;}
    pt operator + (pt t){return {x + t.x, y + t.y};}
    pt operator - (pt t){return {x - t.x, y - t.y};}
    ll operator * (pt t){return x * t.x + y * t.y;}
    ll operator / (pt t){return x * t.y - y * t.x;}
    bool operator == (const pt t)const{return x == t.x && y == t.y;}
    bool operator <(const pt t)const{return x == t.x ? y < t.y : x < t.x;}
    ll szz(){return x * x + y * y;}    
    pt mul(ll m){return {x * m, y * m};}
};

ll ccw(pt a, pt b, pt c) {
    b = b - a, c = c - a;
    return b.x * c.y - c.x * b.y;
}
