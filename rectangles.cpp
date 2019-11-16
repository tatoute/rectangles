#include <map>
#include <utility>
#include <tuple>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std; 

size_t rectangles_axes()
{
    using Coord = int;
    using Point = pair<Coord,Coord>;
    vector<Point > points{
        {0,0},
        {1,0},
        {2,0},
        {0,1},
        {1,1},
        {2,1},
        {0,2},
        {1,2},
        {2,2}
    };
    size_t answer=0;
    map<pair<Coord,Coord> , size_t> count;
    for(auto p: points)
        for(auto p1: points){
            if (p1.first == p.first && p1.second>p.second)
            {
                auto side=make_pair(p.second,p1.second);
                answer+=count[side];
                count[side]++;
            }
        }
    return answer;
}

size_t rectangles()
{
    using Coord = int;
    using Point = pair<Coord,Coord>;
    vector<Point > points;
    for(Coord x=0;x<7;x++)
        for(Coord y=0;y<7;y++)
            points.emplace_back(make_pair(x,y));
    using Side = tuple<Coord,Coord,Coord>;
    map< Side , vector<Point>> count;
    for(auto p: points)
        for(auto p1: points){
            auto dx= p1.first-p.first;
            auto dy= p1.second-p.second;   
            if ((dx>0 || dy>0) && (dx>0 && dy>=0)) // only 1/2 of sides
            {
                auto p2c=make_pair(p.first +p1.first,p.second+p1.second);
                auto h = 
                    (p2c.first )*dx+
                    (p2c.second)*dy;
                auto side = Side(dx,dy,h);
                count[side].push_back(p2c);
            }
        }
    
    size_t answer=0;
    unsigned seed=1112354664;
    for(auto& side : count)
    {
        auto dx= get<0>(side.first);
        auto dy= get<1>(side.first);   
        for(auto it=side.second.begin();it!=side.second.end();it++)
        {
            auto& pc1=*it;
            for(auto it1=it+1;it1!=side.second.end();it1++)
            {
                auto& pc2 = *it1;
            
                Point p0=pc1;
                p0.first-=dx;
                p0.second-=dy;
                Point p1=pc1;
                p1.first+=dx;
                p1.second+=dy;
                Point p2=pc2;
                p2.first+=dx;
                p2.second+=dy;
                Point p3=pc2;
                p3.first-=dx;
                p3.second-=dy;
                cout << "<polygon points='";
                for(auto& corner: {p0,p1,p2,p3})
                    cout << corner.first*100 << " " << corner.second*100 << " ";
                cout << "' stroke='#" << std::setfill('0') << std::setw(6) << std::hex << (seed & 0xffffff) << std::dec << "' fill='#47c54e' fill-opacity='0.2' stroke-width='8'/>" << endl;
                answer++;
                seed = seed * 156862837U + 17692417U;
            }
        }
    }

    return answer;
}


int
main()
{
    cout << "<?xml version='1.0' standalone='no'?>" << endl;
    cout << "<svg width='200' height='250' version='1.1' xmlns='http://www.w3.org/2000/svg'>" << endl;
    auto nb=rectangles();
    cout << "<!-- nb=" << nb << " -->" << endl;
    cout << "</svg>" << endl;
    return 0;
}