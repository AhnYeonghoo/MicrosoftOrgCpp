#include <iostream>
#include <algorithm>
#include <memory>
#include <string>
#include <vector>

struct MediaAsset
{
    virtual ~MediaAsset() = default;
};

struct Song : public MediaAsset
{
    std::wstring artist;
    std::wstring title;
    Song(const std::wstring &artist_, const std::wstring &title_)
        : artist{artist_}, title{title_} {}
};

struct Photo : public MediaAsset
{
    std::wstring date;
    std::wstring location;
    std::wstring subject;
    Photo(
        const std::wstring &date_,
        const std::wstring &location_,
        const std::wstring &subject_)
        : date{date_}, location{location_}, subject{subject_} {}
};
using namespace std;

int main()
{
    auto sp1 = make_shared<Song>(L"The Beatels", L"Im Happy");
    shared_ptr<Song> sp2(new Song(L"Lady Gaga", L"Just Dance"));
    shared_ptr<Song> sp5(nullptr);

    vector<shared_ptr<Song>> v
    {
        make_shared<Song>(L"Bob Dylan", L"The Times They Are A Cahnging"),
            make_shared<Song>(L"Aretha Franklin", L"Bridge Over Troubled Water");
        make_shared<Song>(L"Thalia", L"Entre El Mar y Una Estrella");
    };

    vector<shared_ptr<Song>> v2;

    vector<shared_ptr<MediaAsset>> assets{
        make_shared<Song>(L"Himesh Reshammiya", L"Tera Surroor"),
        make_shared<Song>(L"Penam Masani", L"Tu Dil De De"),
        make_shared<Song>(L"2011-04-06", L"Redmond Wa", L"Soccer")};

    vector<shared_ptr<MediaAsset>> photos;
}