#include "profile.h"
#include "test_runner.h"

#include <iostream>
#include <vector>
#include <utility>
#include <cstdint>
#include <string>
#include <deque>

using namespace std;

struct Booker{
    int64_t _time;
    string _hotel_name;
    int _client_id;
    int _room_count;
};

ostream& operator << (ostream& os, const Booker& b) {
  return os << "{" << b._time << ", " << b._hotel_name << ", " << b._client_id << ", " << b._room_count << "}";
}

class HotelManager{
public:
	HotelManager() {};

    void Book(const int64_t time, const string& hotel_name, const int client_id, const int room_count){
        
        if(hotels.count(hotel_name)){
            hotels[hotel_name].second += room_count;
        } else {
            hotels[hotel_name].second = room_count;
        }
        if(hotels[hotel_name].first.count(client_id)){
            hotels[hotel_name].first[client_id] += room_count;
        } else {
            hotels[hotel_name].first[client_id] = room_count;
        }

        if(!useful_times.empty() && useful_times.back()._time != time){
            UpdateTimes(time);
        }
        useful_times.push_back({time, hotel_name, client_id, room_count});
    }

    int Clients(const string& hotel_name) const {
        return hotels.count(hotel_name) ? hotels.at(hotel_name).first.size() : 0;
    }

    int Rooms(const string& hotel_name) const {
        return hotels.count(hotel_name) ? hotels.at(hotel_name).second : 0;
    }

private:
    static const int SEC_IN_ONE_DAY = 86400;

    deque<Booker> useful_times;
    map<string, pair<map<int, int>, int>> hotels;

    void UpdateTimes(const int64_t newtime){
        while(!useful_times.empty() && newtime - useful_times.front()._time >= SEC_IN_ONE_DAY){
            const string& curr_hotel = useful_times.front()._hotel_name;
            if(hotels[curr_hotel].second == useful_times.front()._room_count){
                hotels.erase(curr_hotel);
            } else {
                hotels[curr_hotel].second -= useful_times.front()._room_count;
                if(hotels[curr_hotel].first[useful_times.front()._client_id] == useful_times.front()._room_count){
                    hotels[curr_hotel].first.erase(useful_times.front()._client_id);
                } else {
                    hotels[curr_hotel].first[useful_times.front()._client_id] -= useful_times.front()._room_count;
                }
            }
            useful_times.pop_front();
        }
    }
};

void Test1()
{
    {
        HotelManager b;
        b.Book(10, "A", 1, 1);
        b.Book(11, "A", 1, 1);
        b.Book(12, "B", 1, 1);
        b.Book(13, "C", 1, 1);
        ASSERT_EQUAL(b.Clients("A"), 1);
        ASSERT_EQUAL(b.Rooms("A"), 2);
    }

    {
        HotelManager b;
        b.Book(10, "A", 1, 1);
        b.Book(11, "A", 2, 2);
        b.Book(12, "B", 1, 1);
        b.Book(13, "C", 1, 1);
        b.Book(86410, "C", 1, 1);
        ASSERT_EQUAL(b.Clients("A"), 1);
        ASSERT_EQUAL(b.Rooms("A"), 2);
    }

    {
        HotelManager b;
        ASSERT_EQUAL(b.Clients("Marriott"), 0);
        ASSERT_EQUAL(b.Rooms("Marriott"), 0);
        b.Book(10, "FourSeasons", 1, 2);
        b.Book(10, "Marriott", 1, 1);
        b.Book(86409, "FourSeasons", 2, 1);
        ASSERT_EQUAL(b.Clients("FourSeasons"), 2);
        ASSERT_EQUAL(b.Rooms("FourSeasons"), 3);
        ASSERT_EQUAL(b.Clients("Marriott"), 1);
        b.Book(86410, "Marriott", 2, 10);
        ASSERT_EQUAL(b.Rooms("FourSeasons"), 1);
        ASSERT_EQUAL(b.Rooms("Marriott"), 10);
    }

    {
        HotelManager b;
        b.Book(10, "A", 1, 1);
        b.Book(11, "A", 2, 2);
        b.Book(12, "B", 1, 1);
        b.Book(13, "C", 1, 1);
        b.Book(86410, "C", 1, 1);
        b.Book(86412, "B", 1, 1);
        b.Book(86412, "B", 2, 2);

        ASSERT_EQUAL(b.Clients("A"), 0);
        ASSERT_EQUAL(b.Rooms("A"), 0);

        ASSERT_EQUAL(b.Clients("B"), 2);
        ASSERT_EQUAL(b.Rooms("B"), 3);

        ASSERT_EQUAL(b.Clients("C"), 1);
        ASSERT_EQUAL(b.Rooms("C"), 2);
    }

    {
        HotelManager b;
        b.Book(1, "A", 1, 1);
        b.Book(2, "A", 1, 2);
        b.Book(86401, "A", 2, 1);
        ASSERT_EQUAL(b.Clients("A"), 2);
    }

    {
        HotelManager b;
        b.Book(1, "A", 1, 1);
        b.Book(2, "A", 2, 2);
        b.Book(86401, "A", 2, 1);
        ASSERT_EQUAL(b.Clients("A"), 1);
    }

    {
        HotelManager b;
        b.Book(1, "A", 1, 1);
        b.Book(1, "A", 2, 2);
        b.Book(1, "A", 2, 2);
        b.Book(86401, "A", 3, 1);
        ASSERT_EQUAL(b.Clients("A"), 1);
        ASSERT_EQUAL(b.Rooms("A"), 1);
    }

    {
        HotelManager b;
        ASSERT_EQUAL(b.Clients("A"), 0);
        b.Book(1, "A", 1, 1);
        b.Book(86401, "B", 2, 1);
        b.Book(86401, "B", 2, 1);
        ASSERT_EQUAL(b.Clients("A"), 0);
        ASSERT_EQUAL(b.Rooms("A"), 0);
        ASSERT_EQUAL(b.Clients("B"), 1);
        ASSERT_EQUAL(b.Rooms("B"), 2);
    }

    {
        HotelManager b;
        b.Book(1, "A", 1, 1);
        b.Book(2, "A", 2, 2);
        b.Book(1000000000000000000, "A", 2, 1);
        ASSERT_EQUAL(b.Clients("A"), 1);
    }

    {
        HotelManager b;
        b.Book(0, "A", 1, 1);
        b.Book(86500, "B", 1, 1);
        ASSERT_EQUAL(b.Clients("A"), 0);
    }

    {
        HotelManager b;
        b.Book(0, "A", 1, 1);
        b.Book(86400, "B", 1, 1);
        b.Book(172'800, "C", 1, 1);
        ASSERT_EQUAL(b.Clients("A"), 0);
        ASSERT_EQUAL(b.Rooms("A"), 0);
        ASSERT_EQUAL(b.Clients("B"), 0);
        ASSERT_EQUAL(b.Rooms("B"), 0);
    }

    {
        HotelManager b;
        b.Book(0, "A", 1, 1);
        b.Book(1, "A", 1, 1);
        b.Book(2, "A", 1, 1);
        ASSERT_EQUAL(b.Clients("A"), 1);
        ASSERT_EQUAL(b.Rooms("A"), 3);
    }

    {
        HotelManager b;
        b.Book(1, "A", 11, 4);
        b.Book(50000, "A", 11, 5);
        b.Book(90000, "A", 22, 2);
        ASSERT_EQUAL(b.Clients("A"), 2);
        ASSERT_EQUAL(b.Rooms("A"), 7);
    }
}

void Test2() {
  HotelManager bm;

  bm.Book(0, "q", 0, 1 );
  ASSERT_EQUAL(bm.Clients("q"), 1);
  ASSERT_EQUAL(bm.Rooms("q"), 1);

  bm.Book( 10, "q", 0, 3 );
  ASSERT_EQUAL(bm.Clients("q"), 1);
  ASSERT_EQUAL(bm.Rooms("q"), 4);

  bm.Book( 86411, "q", 3, 1 );
  ASSERT_EQUAL(bm.Clients("q"), 1);
  ASSERT_EQUAL(bm.Rooms("q"), 1);
}

void Test3() {
    HotelManager manager;

    // Test empty bookings
    ASSERT_EQUAL(manager.Clients("mariott"), 0);
    ASSERT_EQUAL(manager.Rooms("mariott"), 0);

    manager.Book(0, "mariott", 1, 10);
    manager.Book(0, "mariott", 2, 1);
    manager.Book(0, "mariott", 3, 1);
    manager.Book(0, "mariott", 4, 1);
    manager.Book(0, "hilton", 1, 1);
    manager.Book(1, "hilton", 2, 1);

    // Test correctness
    ASSERT_EQUAL(manager.Clients("mariott"), 4);
    ASSERT_EQUAL(manager.Rooms("mariott"), 13);
    ASSERT_EQUAL(manager.Clients("hilton"), 2);
    ASSERT_EQUAL(manager.Rooms("hilton"), 2);

    // Test event past 1 day resets statics
    manager.Book(86400, "mariott", 1, 1);
    ASSERT_EQUAL(manager.Clients("mariott"), 1);
    ASSERT_EQUAL(manager.Rooms("mariott"), 1);
    ASSERT_EQUAL(manager.Clients("hilton"), 1);
    ASSERT_EQUAL(manager.Rooms("hilton"), 1);

    // Test no clients and room for the last day
    manager.Book(86401, "mariott", 5, 1);
    ASSERT_EQUAL(manager.Clients("mariott"), 2);
    ASSERT_EQUAL(manager.Rooms("mariott"), 2);
    ASSERT_EQUAL(manager.Clients("hilton"), 0);
    ASSERT_EQUAL(manager.Rooms("hilton"), 0);
}

void Tester(){
	TestRunner tr;
	RUN_TEST(tr, Test1);
	RUN_TEST(tr, Test2);
	RUN_TEST(tr, Test3);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	Tester();

	HotelManager manager;

	int query_count;
	cin >> query_count;

	for (int query_id = 0; query_id < query_count; ++query_id) {
		string query_type;
		cin >> query_type;

		string hotel_name;

		if (query_type == "BOOK") {
			int64_t time;
			int client_id, room_count;
			cin >> time >> hotel_name >> client_id >> room_count;
			manager.Book(time, hotel_name, client_id, room_count);

		} else if (query_type == "CLIENTS") {
			cin >> hotel_name;
			cout << manager.Clients(hotel_name) << '\n';
		} else if (query_type == "ROOMS") {
			cin >> hotel_name;
			cout << manager.Rooms(hotel_name) << '\n';
		}
	}

	return 0;
}