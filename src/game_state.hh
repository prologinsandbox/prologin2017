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

/// Information about a player; encapsulate its rules::Player_sptr
class Apprentice
{
public:
    /// Constructor from the rules::Player_sptr to encapsulate
    /// `internal_id` is the 0 or 1 position in arrays
    Apprentice(rules::Player_sptr player, int internal_id);

    /// Id of player in GameState arrays
    int get_internal_id() const { return internal_id_; }

    /// Increase the score player (or decrease if a negative value is given)
    void increase_score(int by) { score_ += by; }

    /// Get this player's score (floor of total collected plasma)
    int get_score() const { return score_; }

    /// Syncronize player's score at end of turn
    void synchronize_score() { player_->score = score_; }

    /// Get this player's name
    const std::string& get_name() const { return player_->name; }

    /// Set this player's name (for tests)
    void set_name(const std::string& name) const { player_->name = name; }

    /// Get the list of actions taken by this player last turn
    const std::vector<action_hist>& get_actions() const { return actions_; }

    /// Empty the list of actions at the start of a new turn
    void reset_actions() { actions_.clear(); }

    /// Register a new action
    void add_action(action_hist action) { actions_.push_back(action); }

private:
    rules::Player_sptr player_;        ///< Encapsulated stechec implementation
    std::vector<action_hist> actions_; ///< Actions taken during last turn
    int internal_id_;                  ///< Id of player in GameState arrays
    int score_;                        ///< Player's score
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

    /// Get the players infos
    const auto& get_apprentices() const { return apprentices_; }

    /// Get the score increase when transmuting the given area into gold.
    static int transmute_gold_scoreval(int area);

    /// Get the score increase when transmuting the given area into catalysts.
    static int transmute_catalyst_scoreval(int area);

    /// Get the number of catalysts created by transmuting the given area.
    static int transmute_catalyst_outcome(int area);

    /// Checks whether the given player id is indeed a payer
    bool valid_player(unsigned apprentice_id) const;

    /// Reset all inner state variables only valid during a turn.
    void reset_turn_state();

    /// Perform end of turn checks and actions
    void end_turn(unsigned apprentice_id);

    /// Get the ID of the player currently playing
    int current_player() const { return current_player_; }

    /// Set the player ID currently playing
    void set_current_player(unsigned apprentice_id);

    /// Get a player's score. The id must be valid.
    int get_score(unsigned apprentice_id) const;

    /// Increase a player score (or decrease it if a negative value is given)
    void increase_score(unsigned apprentice_id, int by);

    /// Get number of catalysts available at the moment.
    int get_catalysts_number() const { return catalysts_; }

    /// Increase number of catalysts
    void increase_catalysts_number(int by) { catalysts_ += by; }

    /// Consume a catalyst
    void consume_catalyst() { catalysts_ -= 1; }

    /// Get the sample for the turn.
    echantillon current_sample() const { return sample_; }

    /// Tell if the sample was already placed.
    bool is_sample_placed() const { return sample_placed_; }

    /// Tel if a sample was given this turn.
    bool was_sample_given() const { return sample_given_; }

    /// Place an element on a workbench.
    void place_element(case_type element, position pos, unsigned apprentice_id);

    /// Place a sample on a workbench.
    void place_sample(position pos1, position pos2, unsigned apprentice_id);

    /// Remove the region at a given position and return its size.
    int remove_region(position pos, unsigned apprentice_id);

    /// Change element on given case. Do not consume a catalyst.
    void change_case(position pos, unsigned apprentice_id, case_type new_type);

    /// Set the sample for the opponent's next turn.
    void set_next_sample(echantillon sample);

    /// Tell if a specific sample can be placed at a given location
    bool is_valid_sample_position(echantillon sample, position pos1,
                                  position pos2, unsigned apprentice_id) const;

    /// Get the type of a case at a given position.
    /// Return 'vide' if the position is invalid.
    case_type get_cell_type(position pos, unsigned apprentice_id) const;

    /// Get the element property for the given element.
    static element_propriete get_element_property(case_type element);

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
    void hist_add_catalyze(position pos, unsigned target_apprentice_id,
                           case_type new_type, unsigned apprentice_id);
    void reset_history(unsigned apprentice_id);

    const std::vector<action_hist>& get_history(unsigned apprentice_id) const;

    static constexpr echantillon default_sample = {PLOMB, FER};

    /// Output all data contained by the gamestate on cout, for debug
    void print_state_debug() const;
private:
    std::unordered_map<unsigned, Apprentice> apprentices_;
    std::array<unsigned, 2> apprentices_ids_;

    using Workbench =
        std::array<std::array<case_type, TAILLE_ETABLI>, TAILLE_ETABLI>;
    std::array<Workbench, 2> workbenches_;

    using Connect_components =
        std::array<std::array<int, TAILLE_ETABLI>, TAILLE_ETABLI>;
    std::array<Connect_components, 2> connected_components_;

    void wipe_workbench(unsigned internal_apprentice_id);

    void change_workbench_case(position pos, case_type to,
                               unsigned internal_apprentice_id);

    void merge_connect_components(int from, int to,
                                  unsigned internal_apprentice_id);

    void traverse_and_update_cc(position from, position ignored,
                                Connect_components& ccs);

    bool is_valid_sample_position(echantillon sample, position pos1,
                                  position pos2, const Workbench& workbench,
                                  bool has_elements) const;

    bool has_elements(echantillon sample, const Workbench& workbench) const;

    int turn_;
    int current_player_;
    int catalysts_;
    bool sample_placed_;
    bool sample_given_;
    echantillon sample_;
    echantillon next_sample_;
};

#endif /* !GAME_STATE_HH */
