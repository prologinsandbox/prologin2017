/*
** This file is part of Prologin2017, a rules library for stechec2.
**
** Copyright (c) 2017 Association Prologin <info@prologin.org>
** Copyright (c) 2017 Sacha Delanoue <sacha.delanoue@prologin.org>
**
** Prologin2017 is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** Prologin2017 is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with Prologin2017.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAME_STATE_HH
#define GAME_STATE_HH

#include "constant.hh"

#include <rules/game-state.hh>
#include <rules/player.hh>

#include <array>
#include <unordered_map>

enum class action_type
{
    PLACE,     ///< API function `placer_echantillon`
    TRANSMUTE, ///< API function `transmuter`
    CATALYSE,  ///< API function `catalyser`
    GIVE,      ///< API function `donner_echantillon`
};

struct action
{
    action_type type;  ///< Action type
    position pos1;     ///< Position for PLACE (1st elem), TRANSMUTE, CATALYSE
    position pos2;     ///< Position for PLACE (2nd elem)
    int apprentice_id; ///< Apprentice ID for CATALYZE
    case_type case1;   ///< Case type for CATALYSE, GIVE (1st elem)
    case_type case2;   ///< Case type for GIVE (2nd elem)
};

/// Information about a player; encapsulate its rules::Player_sptr
class Apprentice
{
public:
    /// Constructor from the rules::Player_sptr to encapsulate
    Apprentice(rules::Player_sptr player);

    /// Increase the amount of created gold (thus the score); can be < 0
    void create_gold(int quantity);

    /// Get this player's score (floor of total collected plasma)
    int get_score() const { return player_->score; }

    /// Get this player's name
    const std::string& get_name() const { return player_->name; }

    /// Set this player's name (for tests)
    void set_name(const std::string& name) const { player_->name = name; }

    /// Get the list of actions taken by this player last turn
    const std::vector<action>& get_actions() const { return actions_; }

    /// Empty the list of actions at the start of a new turn
    void reset_actions() { actions_.clear(); }

    /// Register a new action
    void add_action(action action) { actions_.push_back(action); }

private:
    rules::Player_sptr player_;   ///< Encapsulated stechec implementation
    std::vector<action> actions_; ///< Actions taken during last turn
};

class GameState : public rules::GameState
{
public:
    GameState(rules::Players_sptr players);
    rules::GameState* copy() const override;

    void increment_turn() { turn_++; }
    int get_turn() const { return turn_; }
    unsigned opponent(unsigned player) const
    {
        return (apprentices_ids_[0] == player) ? apprentices_ids_[1]
                                               : apprentices_ids_[0];
    }

    /// Reset all inner state variables only valid during a turn.
    void reset_turn_state();

    /// Get a player's score. The id must be valid.
    int get_score(unsigned apprentice_id) const;

    /// Get number of catalysts available at the moment.
    int get_catalysts_number() const { return catalysts_; }

    /// Get the sample for the turn.
    echantillon current_sample() const { return sample_; }

    /// Tell if the sample was already placed.
    bool is_sample_placed() const { return sample_placed_; }

    /// Place a sample on a workbench.
    void place_sample(position pos1, position pos2, unsigned apprentice_id);

    /// Activate the region at a given position.
    void transmute(position pos, unsigned apprentice_id);

    /// Change element on given case. Consume a catalyst.
    void catalyze(position pos, unsigned apprentice_id, case_type new_type);

    /// Set the sample for the opponent's next turn.
    void give(echantillon sample);

    /// Get the type of a case at a given position.
    /// Return 'vide' if the position is invalid.
    case_type get_cell_type(position pos, unsigned apprentice_id) const;

    /// Get the size of the region containing the position.
    /// Return -1 if position is invalid.
    int get_region_size(position pos, unsigned apprentice_id) const;

    /// Get the position of all cases of a region containing a given position
    std::vector<position> get_region(position p, unsigned apprentice_id) const;

    /// Get all the posible locations for a sample an a workbench
    std::vector<position_echantillon>
    possible_sample_positions(echantillon sample, unsigned apprentice_id) const;

    // Update action history
    void hist_add_place(position pos1, position pos2, unsigned apprentice_id);
    void hist_add_transmute(position pos, unsigned apprentice_id);
    void hist_add_catalize(position pos, unsigned target_apprentice_id,
                           case_type new_type, unsigned apprentice_id);
    void hist_add_give(echantillon sample, unsigned apprentice_id);
    void reset_history(unsigned apprentice_id);

    const std::vector<action>& get_history(unsigned apprentice_id) const;

private:
    std::unordered_map<unsigned, Apprentice> apprentices_;
    std::array<unsigned, 2> apprentices_ids_;

    using Workbench =
        std::array<std::array<case_type, TAILLE_ETABLI>, TAILLE_ETABLI>;
    std::array<Workbench, 2> workbenches_;

    using Connect_components =
        std::array<std::array<int, TAILLE_ETABLI>, TAILLE_ETABLI>;
    std::array<Connect_components, 2> connected_components_;

    int turn_;
    int catalysts_;
    bool sample_placed_;
    echantillon sample_;
    echantillon next_sample_;
};

#endif /* !GAME_STATE_HH */
