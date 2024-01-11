package automata;

import java.util.Set;
import java.util.stream.Collectors;

public class RegExp implements Automaton.RegExpConverter<DetAutomaton, NonDetAutomaton> {
  @Override
  public NonDetAutomaton regExpToNFA (String r, Set<Character> alphabet) {
    // TODO: Fill this.

    NonDetAutomaton A = new NonDetAutomaton (alphabet);
    A.addState ("q0");
    A.setInitial ("q0");
    return A;
  }

  @Override
  public NonDetAutomaton regExpToNFA (String r, String alph) {
    // Converts a string to a set of character. Included for convenience.
    // DO NOT TOUCH.
    return regExpToNFA (r, alph.chars ().mapToObj (e -> (char) e).collect (Collectors.toSet ()));
  }

  /// NFA to RegExp
  @Override
  public String NFAToRegExp (NonDetAutomaton A) {
    // TODO: Fill this.
    return "a";
  }
}
