# Game Bot for Strategic Card Game

This project is a C++ implementation of an intelligent bot designed for a custom card game. The game itself is a hybrid inspired by popular games such as Blackjack, Poker, and even strategic board games like Chess and Go. The design philosophy behind both the game and the bot emphasizes simplicity in rules, while ensuring that the strategic depth arises from the interplay of probabilities, betting mechanics, and human psychology.

---

## Table of Contents
- [Introduction](#introduction)
- [Game Overview](#game-overview)
- [Game Mechanics](#game-mechanics)
  - [Card Mechanics](#card-mechanics)
  - [Betting Mechanics](#betting-mechanics)
- [Mathematical Foundations](#mathematical-foundations)
  - [Win Probability Calculation](#win-probability-calculation)
  - [Expected Value of Drawing a Card](#expected-value-of-drawing-a-card)
  - [Algorithmic Complexity](#algorithmic-complexity)
- [Bot Parameters and Strategies](#bot-parameters-and-strategies)
  - [Bluffing Mechanism](#bluffing-mechanism)
  - [Bet Distribution](#bet-distribution)
  - [Player Reaction Modeling](#player-reaction-modeling)
- [Game Parameters and Their Influence](#game-parameters-and-their-influence)
- [Win Probability Adjustments: Simple, Assumed, and Complex](#win-probability-adjustments-simple-assumed-and-complex)
- [Conclusion](#conclusion)
- [License](#license)

---

## Introduction

This project documents the creation and underlying logic of a bot for a custom-designed card game. The game was developed over many sessions and based on countless experiences with similar strategic games. If you are only interested in the mathematical aspects and the bot’s decision-making process, you may skip the narrative sections that describe the design journey. However, those curious about the deeper conceptual background will find value in the full explanation.

---

## Game Overview

The game is a synthesis of Blackjack and Poker, where each player starts with an equal amount of money. The main objective is straightforward: to win all of the other players' money. Unlike conventional card games that might be overly reliant on chance, this game’s rules are designed to reward strategy, skill, and psychological insight. Minimalistic rules promote natural strategic complexity rather than an overburden of arbitrary or “artificial” rules.

---

## Game Mechanics

### Card Mechanics

- **Card Values:**  
  - Numbered cards have their face value.  
  - Face cards (Jack, Queen, King) are each valued at 10.  
  - Aces can be counted as either 1 or 11, at the player’s discretion.
- **Hand Evaluation:**  
  - The value of a hand is the sum of its cards.  
  - If the sum exceeds 21, the hand value becomes 0.  
  - A five-card hand that does not exceed 21 is automatically considered as having a value of 21, even if its sum would be less.
- **Gameplay Flow:**  
  - Cards are drawn face down, and once used in a round, they are moved to a discard pile.  
  - When the main deck runs low, the discard pile is shuffled back into play.

### Betting Mechanics

- **Blind Bet:**  
  - At the start of each round, every player places a blind bet (a fixed fraction, e.g., 1/5 of their starting money) into the pot.
- **Distribution of Cards:**  
  - Each player receives one card face up and one card face down.
- **Bet Increases:**  
  - Players may increase the pot only if two conditions are met:  
    1. The maximum raise for that round has not been reached.  
    2. The raised bet does not exceed what the poorest active player can cover.
- **Round Conclusion:**  
  - When all active players signal they are ready (via a “green light” gesture), hands are revealed.  
  - The player with the highest hand value wins the pot. In the event of a tie, the pot is divided equally (any remainder carries over to the next round).
- **Additional Rules:**  
  - A player may not draw more than three cards per round.  
  - If a player chooses to draw a card, the drawn card must be taken without previewing and then immediately added to the hand.
  - There is a mechanic for discarding cards secretly, which can be used strategically when only one opponent remains.

---

## Mathematical Foundations

### Win Probability Calculation

For a given round, let:  
- **m** be the number of known cards in the deck,  
- **n** be the number of unknown cards (from the opponent’s perspective), and  
- **s** be the number of combinations given by the binomial coefficient:  
  \[
  s = \binom{m}{n} = \frac{m!}{(m-n)! \, n!}
  \]

The win probability \( P_w \) is computed as:
\[
P_w = \frac{\sum_{k=1}^{s} P_k}{s}
\]
Here, \( P_k \) is not the probability of the \( k \)-th event occurring per se but the winning probability resulting from assigning the \( k \)-th combination of cards to the opponent. In any situation, this value will be either 1 or 0.

### Expected Value of Drawing a Card

Since every possible combination is considered as an independent scenario, the expected value \( V \) of drawing an extra card is:
\[
V = \frac{\sum_{k=1}^{s} V_k}{s}
\]
where
\[
V_k = \sum_{j=1}^{(m-n)} \frac{(P_j - P_i)}{(m-n)}
\]
- \( P_j \) is the win probability after drawing the \( j \)-th card.
- \( P_i \) is the win probability if no additional card is drawn.
  
Expanding these sums, the overall equation becomes:
\[
V = \sum_{k=1}^{s} \left( \frac{ \sum_{j=1}^{(m-n)} (P_j - P_i)}{(m-n) \, s} \right)
\]

A positive \( V \) suggests that drawing a card is a favorable move.

### Algorithmic Complexity

The time complexity of the algorithm to compute these values is:
\[
O\left(\frac{n! \, (n-m)}{(n-m)! \, m!}\right)
\]
or, in a simplified form:
\[
O\left(\frac{n!}{(n-m-1)! \, m!}\right)
\]

---

## Bot Parameters and Strategies

The bot uses a number of parameters to mimic intelligent play:

- **Bluff Probability (P_bluff):**  
  When the win probability \( P_w \) is below the critical threshold of 0.5, the bot may decide to place a large bet as a bluff.
  
- **Bluff Distribution:**  
  To ensure unpredictability in the bet amounts during a bluff, the bot uses a probability distribution. One suitable candidate for this is the Gaussian (normal) distribution:
  \[
  f(x) = \frac{1}{\sigma \sqrt{2\pi}} e^{-\frac{1}{2}\left(\frac{x-\mu}{\sigma}\right)^2}
  \]
  This distribution is parameterized by the mean (\( \mu \)) and the standard deviation (\( \sigma \)).

- **Call Threshold:**  
  The minimum win probability required for the bot to ‘call’ (i.e., to respond to an opponent’s raise) is defined by:
  \[
  m_{call} \leq P_w \, m_{rmax}
  \]
  where \( m_{rmax} \) is the maximum bet raise possible.
  
- **Bet Divider:**  
  To avoid exploitation of the betting raise rule, a conceptual threshold is set which limits the maximum bet the bot will consider.

- **Minimum Win Probability for Raising:**  
  The bot will only increase the bet if its win probability exceeds a predefined threshold (\( P_{rmin} \)).

---

## Game Parameters and Their Influence

Key game parameters include:

- **Starting Money (m_start):**  
  The amount of money each player starts with. This value is chosen such that subsequent calculations with other parameters do not result in cumbersome decimals.
  
- **Blind Bet Ratio (Q_blind):**  
  The fraction of the starting money that each player must place in the pot at the beginning of every round.
  
- **Maximum Raise Ratio (Q_maxraise):**  
  The maximum amount by which the bet can be increased relative to the blind bet.

These game parameters directly influence the bot’s internal parameters. For example, the minimum win probability for calling, \( P_{cmin} \), can be derived as:
\[
P_{cmin} = 1 - (Q_{blind} - Q_{maxraise})
\]
This formulation allows the bot to adapt its strategy based on the game’s length and betting dynamics.

---

## Win Probability Adjustments: Simple, Assumed, and Complex

The bot distinguishes between three win probability calculations:

1. **Simple Win Probability (\( P_{simple} \))**  
   Calculated solely on the known and unknown card counts. For example, if there are four unknown cards and two favorable outcomes, then \( P_{simple} = \frac{2}{4} \).

2. **Assumed Win Probability (\( P_{assumed} \))**  
   This value is estimated by constructing game trees based on the opponent’s possible moves. In cases like ties, probabilities are adjusted (e.g., multiplied by 0.5).

3. **Complex Win Probability (\( P_{complex} \))**  
   A weighted combination of the two probabilities above:
   \[
   P_{complex} = (1 - W_{assumed}) \cdot P_{simple} + W_{assumed} \cdot P_{assumed}
   \]
   where \( W_{assumed} \) is the weight factor representing the confidence in the assumed probability.  
   
   **Example:**  
   Given a deck with cards `[2, 4, 7, 9, 10, 10, 11]` (with 11 representing an Ace) and the bot’s hand of `[10, 7]` against an opponent’s visible 10:
   - The game tree might yield several win probability values for different terminal states.
   - After averaging (including adjustments for tie situations), suppose \( P_{assumed} = 0.4164 \).
   - If the simple calculation gives \( P_{simple} = 0.5 \) and \( W_{assumed} \) is chosen as 0.2, then:
     \[
     P_{complex} = 0.8 \times 0.5 + 0.2 \times 0.4164 \approx 0.4832
     \]
   This combined value helps the bot decide whether to call, raise, or fold based on real-time evaluations of the game state.

---

## Conclusion

This C++ project models a bot for a complex card game that combines elements of chance, skill, and psychological strategy. By using detailed probability calculations, expected value assessments, and dynamic parameter adjustments, the bot is designed to make informed decisions in a game where both the rules and human behavior play critical roles. The interplay between game mechanics and bot strategy ensures that even as the game evolves, the bot adapts its decisions based on both statistical evidence and modeled opponent behavior.

---

## License

N/A. I mean, I don't need it, I guess?

