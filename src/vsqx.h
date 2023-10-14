#ifndef VSQX_H
#define VSQX_H

#include <array>
#include <string>
#include <vector>
#include <cstdint>
#include <iostream>
#include <tinyxml2.h>
#include "xml.h"

namespace NoteBlade {
    typedef std::uint64_t VSQXUInt;

    enum VSQXNotePitch : VSQXUInt {
        C_2 = 0,   Cs_2 = 1,   D_2 = 2,   Eb_2 = 3,   E_2 = 4,   F_2 = 5,   Fs_2 = 6,   G_2 = 7,   Gs_2 = 8,   A_2 = 9,   Bb_2 = 10,  B_2 = 11,
        C_1 = 12,  Cs_1 = 13,  D_1 = 14,  Eb_1 = 15,  E_1 = 16,  F_1 = 17,  Fs_1 = 18,  G_1 = 19,  Gs_1 = 20,  A_1 = 21,  Bb_1 = 22,  B_1 = 23,
        C0  = 24,  Cs0  = 25,  D0  = 26,  Eb0  = 27,  E0  = 28,  F0  = 29,  Fs0  = 30,  G0  = 31,  Gs0  = 32,  A0  = 33,  Bb0  = 34,  B0  = 35,
        C1  = 36,  Cs1  = 37,  D1  = 38,  Eb1  = 39,  E1  = 40,  F1  = 41,  Fs1  = 42,  G1  = 43,  Gs1  = 44,  A1  = 45,  Bb1  = 46,  B1  = 47,
        C2  = 48,  Cs2  = 49,  D2  = 50,  Eb2  = 51,  E2  = 52,  F2  = 53,  Fs2  = 54,  G2  = 55,  Gs2  = 56,  A2  = 57,  Bb2  = 58,  B2  = 59,
        C3  = 60,  Cs3  = 61,  D3  = 62,  Eb3  = 63,  E3  = 64,  F3  = 65,  Fs3  = 66,  G3  = 67,  Gs3  = 68,  A3  = 69,  Bb3  = 70,  B3  = 71,
        C4  = 72,  Cs4  = 73,  D4  = 74,  Eb4  = 75,  E4  = 76,  F4  = 77,  Fs4  = 78,  G4  = 79,  Gs4  = 80,  A4  = 81,  Bb4  = 82,  B4  = 83,
        C5  = 84,  Cs5  = 85,  D5  = 86,  Eb5  = 87,  E5  = 88,  F5  = 89,  Fs5  = 90,  G5  = 91,  Gs5  = 92,  A5  = 93,  Bb5  = 94,  B5  = 95,
        C6  = 96,  Cs6  = 97,  D6  = 98,  Eb6  = 99,  E6  = 100, F6  = 101, Fs6  = 102, G6  = 103, Gs6  = 104, A6  = 105, Bb6  = 106, B6  = 107,
        C7  = 108, Cs7  = 109, D7  = 110, Eb7  = 111, E7  = 112, F7  = 113, Fs7  = 114, G7  = 115, Gs7  = 116, A7  = 117, Bb7  = 118, B7  = 119,
        C8  = 120, Cs8  = 121, D8  = 122, Eb8  = 123, E8  = 124, F8  = 125, Fs8  = 126, G8  = 127,
    };

    const static std::array<std::string, 128> VSQXNotePitchName = {
        "C-2", "C#-2", "D-2", "Eb-2", "E-2", "F-2", "F#-2", "G-2", "G#-2", "A-2", "Bb-2", "B-2",
        "C-1", "C#-1", "D-1", "Eb-1", "E-1", "F-1", "F#-1", "G-1", "G#-1", "A-1", "Bb-1", "B-1",
        "C0",  "C#0",  "D0",  "Eb0",  "E0",  "F0",  "F#0",  "G0",  "G#0",  "A0",  "Bb0",  "B0",
        "C1",  "C#1",  "D1",  "Eb1",  "E1",  "F1",  "F#1",  "G1",  "G#1",  "A1",  "Bb1",  "B1",
        "C2",  "C#2",  "D2",  "Eb2",  "E2",  "F2",  "F#2",  "G2",  "G#2",  "A2",  "Bb2",  "B2",
        "C3",  "C#3",  "D3",  "Eb3",  "E3",  "F3",  "F#3",  "G3",  "G#3",  "A3",  "Bb3",  "B3",
        "C4",  "C#4",  "D4",  "Eb4",  "E4",  "F4",  "F#4",  "G4",  "G#4",  "A4",  "Bb4",  "B4",
        "C5",  "C#5",  "D5",  "Eb5",  "E5",  "F5",  "F#5",  "G5",  "G#5",  "A5",  "Bb5",  "B5",
        "C6",  "C#6",  "D6",  "Eb6",  "E6",  "F6",  "F#6",  "G6",  "G#6",  "A6",  "Bb6",  "B6",
        "C7",  "C#7",  "D7",  "Eb7",  "E7",  "F7",  "F#7",  "G7",  "G#7",  "A7",  "Bb7",  "B7",
        "C8",  "C#8",  "D8",  "Eb8",  "E8",  "F8",  "F#8",  "G8",
    };

    class VSQXSinger {
        public:
            struct VSQXSingerRecord {
                VSQXUInt     number;
                std::string  name;
                std::string  id;
            };
            VSQXSinger(VSQXSingerRecord data) : record(data) {};

        private:
            VSQXSingerRecord record;
        public:
            VSQXUInt     number()   const { return record.number; };
            std::string  name()     const { return record.name; };
            std::string  id()       const { return record.id; };
            void         display()  const;
    };

    class VSQXNote {
        public:
            struct VSQXNoteRecord {
                VSQXUInt       start_tick;
                VSQXUInt       duration_tick;
                VSQXNotePitch  pitch;
                bool           xsampa_locked;
                std::string    xsampa;
                std::string    lyric;
            };
            VSQXNote(VSQXNoteRecord data) : record(data) {};

        private:
            VSQXNoteRecord record;
        public:
            VSQXUInt       start_tick()        const  { return record.start_tick; };
            VSQXUInt       duration_tick()     const  { return record.duration_tick; };
            VSQXNotePitch  pitch()             const  { return record.pitch; };
            bool           xsampa_locked()     const  { return record.xsampa_locked; };
            std::string    xsampa()            const  { return record.xsampa; };
            std::string    lyric()             const  { return record.lyric; };
            void           display()           const; 

            std::string    pitch_name()        const  { return VSQXNotePitchName[pitch()]; };
            std::string    pronunciation()     const  { return xsampa_locked() ? xsampa() : lyric(); };
    };

    class VSQXPart {
        public:
            struct VSQXPartRecord {
                VSQXUInt               start_tick;
                std::vector<VSQXNote>  notes;
            };
            VSQXPart(VSQXPartRecord data) : record(data) {};

        private:
            VSQXPartRecord record;
        public:
            VSQXUInt               start_tick()          const  { return record.start_tick; };
            std::vector<VSQXNote>  notes()               const  { return record.notes; };
            void                   display()             const; 

            VSQXNote               note(VSQXUInt i)      const  { return notes().at(i); };
            VSQXUInt               notes_size()          const  { return notes().size(); };
            void                   notes_create(VSQXNote note)  { record.notes.push_back(note); };
    };

    class VSQXTrack {
        public:
            struct VSQXTrackRecord
            {
                VSQXUInt               number;
                std::string            name;
                std::vector<VSQXPart>  parts;
            };
            VSQXTrack(VSQXTrackRecord data) : record(data) {};
        
        private:
            VSQXTrackRecord record;
        public:
            VSQXUInt               number()              const  { return record.number; };
            std::string            name()                const  { return record.name; };
            std::vector<VSQXPart>  parts()               const  { return record.parts; };
            void                   display()             const; 
 
            VSQXPart               part(VSQXUInt i)      const  { return parts().at(i); };
            VSQXUInt               parts_size()          const  { return parts().size(); };
            void                   parts_create(VSQXPart part)  { record.parts.push_back(part); };
    };

    class VSQXProject {
        public:
            struct VSQXProjectRecord {
                VSQXUInt                 pre_measure;
                VSQXUInt                 tick_per_beat;
                VSQXUInt                 time_signture_numerator;
                VSQXUInt                 time_signture_denominator;
                std::vector<VSQXSinger>  singers;
                std::vector<VSQXTrack>   tracks;
            };
            VSQXProject(VSQXProjectRecord data) : record(data) {};

        private:
            VSQXProjectRecord record;
        public:
            VSQXUInt                 pre_measure()                const  { return record.pre_measure; };
            VSQXUInt                 tick_per_beat()              const  { return record.tick_per_beat; };
            VSQXUInt                 time_signture_numerator()    const  { return record.time_signture_numerator; };
            VSQXUInt                 time_signture_denominator()  const  { return record.time_signture_denominator; };
            std::vector<VSQXSinger>  singers()                    const  { return record.singers; };
            std::vector<VSQXTrack>   tracks()                     const  { return record.tracks; };
            void                     display()                    const;
            void                     display_singer(VSQXUInt i)   const;
            void                     display_track(VSQXUInt i)    const;

            std::string              time_signture()              const  { return std::to_string(time_signture_numerator()) + "/" + std::to_string(time_signture_denominator()); };
            VSQXUInt                 tick(VSQXUInt beat)          const  { return beat * tick_per_beat(); };
            VSQXSinger               singer(VSQXUInt i)           const  { return singers().at(i); };
            VSQXSinger               singer_no(VSQXUInt i)        const; 
            std::vector<VSQXUInt>    singer_ids()                 const; 
            VSQXUInt                 singers_size()               const  { return singers().size(); };
            void                     singers_create(VSQXSinger singer)   { record.singers.push_back(singer); };
            VSQXTrack                track(VSQXUInt i)            const  { return tracks().at(i); };
            VSQXTrack                track_no(VSQXUInt i)         const; 
            std::vector<VSQXUInt>    track_ids()                  const; 
            VSQXUInt                 tracks_size()                const  { return tracks().size(); };
            void                     tracks_create(VSQXTrack track)      { record.tracks.push_back(track); };
    };

    class VSQXReader {
        private:
            XML          _xml;
            VSQXProject  _project;
            void load_metadata();
            void load_singers();
            void load_tracks();
        public:
            VSQXReader(std::string path);
            XML         xml()     const { return _xml; };
            VSQXProject project() const { return _project; };
    };
}

#endif
