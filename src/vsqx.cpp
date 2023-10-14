#include <iomanip>
#include "xml.h"
#include "vsqx.h"
#include "error.h"
#include "display.h"

void NoteBlade::VSQXSinger::display() const
{
    std::cout << "VSQXSinger @"  << DISPLAY_ADDRESS(this) << std::endl;
    std::cout << "  number:    " << number()              << std::endl;
    std::cout << "  name:      " << name()                << std::endl;
    std::cout << "  id:        " << id()                  << std::endl;
    std::cout << std::endl;
}

void NoteBlade::VSQXNote::display() const
{
    std::cout << "VSQXNote @"          << DISPLAY_ADDRESS(this) << std::endl;
    std::cout << "  start_tick:      " << start_tick()          << std::endl;
    std::cout << "  duration_tick:   " << duration_tick()       << std::endl;
    std::cout << "  pitch:           " << pitch() << " ("       << pitch_name() << ")" << std::endl;
    std::cout << "  xsampa_locked:   " << std::noboolalpha      << xsampa_locked() << std::endl;
    std::cout << "  xsampa:          " << xsampa()              << std::endl;
    std::cout << "  lyric:           " << lyric()               << std::endl;
    std::cout << "  pronunciation(): " << pronunciation()       << std::endl;
    std::cout << std::endl;
}

void NoteBlade::VSQXPart::display() const
{
    std::cout << "VSQXPart @"       << DISPLAY_ADDRESS(this) << std::endl;
    std::cout << "  start_tick:   " << start_tick()          << std::endl;
    std::cout << "  notes_size(): " << notes_size()          << std::endl;
    std::cout << std::endl;
}

void NoteBlade::VSQXTrack::display() const
{
    std::cout << "VSQXTrack @"      << DISPLAY_ADDRESS(this) << std::endl;
    std::cout << "  name:         " << name()                << std::endl;
    std::cout << "  parts_size(): " << parts_size()          << std::endl;
    std::cout << std::endl;
}

void NoteBlade::VSQXProject::display() const
{
    std::cout << "VSQXProject @"       << DISPLAY_ADDRESS(this) << std::endl;
    std::cout << "  pre_measure:     " << pre_measure()         << std::endl;
    std::cout << "  tick_per_beat:   " << tick_per_beat()       << std::endl;
    std::cout << "  time_signture(): " << time_signture()       << std::endl;
    std::cout << "  singers:         " << "size() = "           << singers_size() << std::endl;
    for (VSQXUInt i = 0; i < singers_size(); i++) display_singer(i);
    std::cout << "  tracks:          " << "size() = "           << tracks_size()  << std::endl;
    for (VSQXUInt i = 0; i < tracks_size(); i++)  display_track(i);
    std::cout << std::endl;
}

void NoteBlade::VSQXProject::display_singer(VSQXUInt i) const
{
    std::cout << "                   " << "#" << std::left << std::setw(4) << singer(i).number() << " [" << singer(i).name() << "]" << std::endl;
}

void NoteBlade::VSQXProject::display_track(VSQXUInt i) const
{
    std::cout << "                   " << "#" << std::left << std::setw(4) << track(i).number()  << " [" << track(i).name() << "]"  << std::endl;
}

NoteBlade::VSQXSinger NoteBlade::VSQXProject::singer_no(VSQXUInt i) const
{
    for (auto singer : singers())
    {
        if (singer.number() == i) return singer;
    }
    throw std::out_of_range(
        ERR_NUMBER_FORMAT_MESSAGE(ERR_SINGER_NOT_FOUND) + ": " +
        "Singer with number '" + std::to_string(i) + "' not found. Is the VSQX file damaged?"
    );
}

std::vector<NoteBlade::VSQXUInt> NoteBlade::VSQXProject::singer_ids() const
{
    auto ids = std::vector<VSQXUInt>();
    for (auto singer : singers()) ids.push_back(singer.number());
    return ids;
}

NoteBlade::VSQXTrack NoteBlade::VSQXProject::track_no(VSQXUInt i) const
{
    for (auto track : tracks())
    {
        if (track.number() == i) return track;
    }
    throw std::out_of_range(
        ERR_NUMBER_FORMAT_MESSAGE(ERR_TRACK_NOT_FOUND) + ": " +
        "Track with number '" + std::to_string(i) + "' not found. Is the VSQX file damaged?"
    );
}

std::vector<NoteBlade::VSQXUInt> NoteBlade::VSQXProject::track_ids() const
{
    auto ids = std::vector<VSQXUInt>();
    for (auto track : tracks()) ids.push_back(track.number());
    return ids;
}

NoteBlade::VSQXReader::VSQXReader(std::string path) : _xml(XML(path)), _project(VSQXProject::VSQXProjectRecord())
{
    load_metadata();
    load_singers();
    load_tracks();
}


void NoteBlade::VSQXReader::load_metadata()
{
    auto project = VSQXProject::VSQXProjectRecord {
        .pre_measure               = _xml.root().first("masterTrack").first("preMeasure")         .as_uint().unwarp(),
        .tick_per_beat             = _xml.root().first("masterTrack").first("resolution")         .as_uint().unwarp(),
        .time_signture_numerator   = _xml.root().first("masterTrack").first("timeSig").first("nu").as_uint().unwarp(),
        .time_signture_denominator = _xml.root().first("masterTrack").first("timeSig").first("de").as_uint().unwarp(),
    };
    _project = VSQXProject(project);
}

void NoteBlade::VSQXReader::load_singers()
{
    auto singers = _xml.root().first("vVoiceTable").select("vVoice");
    for (auto singer : singers) {
        if (singer.null()) continue;
        _project.singers_create(NoteBlade::VSQXSinger(NoteBlade::VSQXSinger::VSQXSingerRecord {
            .number = singer.first("pc")  .as_uint().unwarp(),
            .name   = singer.first("name").as_string().unwarp(),
            .id     = singer.first("id")  .as_string().unwarp(),
        }));
    }
}

#include <iostream>

void NoteBlade::VSQXReader::load_tracks()
{
    auto tracks = _xml.root().select("vsTrack");
    for (auto track : tracks) {
        auto _track = NoteBlade::VSQXTrack(NoteBlade::VSQXTrack::VSQXTrackRecord {
            .number = track.first("tNo") .as_uint().unwarp(),
            .name   = track.first("name").as_string().unwarp(),
        });
        auto parts = track.select("vsPart");
        for (auto part : parts) {
            auto _part = NoteBlade::VSQXPart(NoteBlade::VSQXPart::VSQXPartRecord {
                .start_tick = part.first("t").as_uint().unwarp(),
            });
            auto notes = part.select("note");
            for (auto note : notes) {
                _part.notes_create(NoteBlade::VSQXNote(NoteBlade::VSQXNote::VSQXNoteRecord {
                    .start_tick     = note.first("t")  .as_uint().unwarp(),
                    .duration_tick  = note.first("dur").as_uint().unwarp(),
                    .pitch          = NoteBlade::VSQXNotePitch(note.first("n").as_uint().unwarp()),
                    .xsampa_locked  = note.first("p")  .attr_bool("lock").default_unwarp(false),
                    .xsampa         = note.first("p")  .as_string().default_unwarp(""),
                    .lyric          = note.first("y")  .as_string().default_unwarp(""),
                }));
            }
            _track.parts_create(_part);
        }
        _project.tracks_create(_track);
    }
}

