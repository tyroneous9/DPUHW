package automata;

import java.util.Collections;
import java.util.Stack;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.Map.Entry;
import java.util.stream.Collectors;

public class NonDetAutomaton extends Automaton implements Automaton.NonDeterminism<DetAutomaton> {
  // Suggested:
  // private Map<Pair<String, Character>, Set<String>> delta;
  private Map<Pair<String, Character>, Set<String>> transitions;
  private Set<Character> alphabet;
  private Set<String> states;
  private Set<String> finalStates;
  private String initialState;

  /**
   * Create an automaton on a given alphabet. {@link EPSILON} will never be part
   * of the input alphabet.
   * 
   * @param alph The alphabet of the automaton, can be EMPTY_SET.
   */
  public NonDetAutomaton (Set<Character> alph) {
    // TODO: Fill this.
	  transitions = new HashMap<Pair<String, Character>, Set<String>>();
	  this.alphabet = new HashSet<>(alph);
	  states = new HashSet<>();
	  finalStates = new HashSet<>();
	  initialState = "";
  }

  /**
   * Create an automaton on a given alphabet.
   * 
   * @param alph The alphabet of the automaton, as a String, each character
   *             being a letter of the alphabet.
   */
  public NonDetAutomaton (String alph) {
    this (alph.chars ().mapToObj (e -> (char) e).collect (Collectors.toSet ()));
  }

  /**
   * Alphabet of the automaton.
   * 
   * @return The alphabet of the automaton.
   */
  @Override
  public Set<Character> getAlphabet () {
    // TODO: Fill this.
    return alphabet;
  }

  /**
   * Add a state to the automaton.
   * 
   * @param q The state to add.
   */
  @Override
  public void addState (String q) {
    // TODO: Fill this.
	  states.add(q);
  }

  /**
   * Add a transition to the automaton.
   * 
   * @param p     State from which the transition goes.
   * @param label Label of the transition, can be {@link EPSILON}.
   * @param q     State to which the transition goes.
   */
  @Override
  public void addTransition (String p, char label, String q) {
    // TODO: Fill this.
    // /!\ label can be Automaton.EPSILON;
	Pair<String, Character> pair = new Pair<>(p,label);
	if(!transitions.containsKey(pair)) {
		transitions.put( pair, new HashSet<String>());
	}
	transitions.get(pair).add(q);
	
  }

  // Suggested: helper function, closure under epsilon transitions.
  private Set<String> E(Set<String> S) {
    Set<String> result = new HashSet<>(S);
    Stack<String> stack = new Stack<>();
    stack.addAll(S);
    
    while (!stack.isEmpty()) {
        String s = stack.pop();
        Set<String> subEpTrans = transitions.get(new Pair<String,Character>(s, EPSILON));
        if (subEpTrans != null) {
            for (String subS : subEpTrans) { 
	            result.add(subS);
	            stack.push(subS);
            }
        }
    }
    return result;
  }


  /**
   * Check whether a word is accepted by the automaton.
   * 
   * @param w An input word.
   * @return Whether the automaton accepts the input word.
   */
  @Override
  public boolean accepts (String w) {
    // TODO: Fill this.
    // Suggested: Use E above.
	    Set<String> currStates = new HashSet<>();
	    currStates.add(initialState);

	    for (int i = 0; i < w.length(); i++) {
	        Set<String> nextStates = new HashSet<>();
	        //
	        for (String state : currStates) {
	            Set<String> subTrans = transitions.get(new Pair<String,Character>(state, w.charAt(i)));
	            if (subTrans != null) {
	                nextStates.addAll(subTrans);
	            }
	        }
	        currStates = E(nextStates);
	    }

	    return !Collections.disjoint(currStates, finalStates);
  }

  /**
   * Set a state to be final.
   * 
   * @param q State to add to the set of final states.
   */
  @Override
  public void setFinal (String q) {
    // TODO: Fill this.
	  finalStates.add(q);
  }

  /**
   * Return the set of final states.
   * 
   * @return The set of final states.
   */
  @Override
  public Set<String> getFinal () {
    // TODO: Fill this.
	  return finalStates;
  }

  /**
   * Set a state to be initial.
   * 
   * @param q The state to set as initial.
   */
  @Override
  public void setInitial (String q) {
    // TODO: Fill this.
	  initialState = q;
  }

  /**
   * Get the initial state.
   * 
   * @return The initial state.
   */
  @Override
  public String getInitial () {
    // TODO: Fill this.
    return initialState;
  }

  /**
   * Return the set of states.
   * 
   * @return The set of states.
   */
  @Override
  public Set<String> getStates () {
    // TODO: Fill this.
    return states;
  }

  /**
   * Get all transitions from a given state.
   * 
   * @param p The state of which we want the outgoing transitions.
   * @return The set of outgoing transitions, where each outgoing transition is a
   *         pair (label, destination).
   */
  @Override
  public Set<Pair<Character, String>> getTransitionsFrom (String p) {
    // TODO: Fill this.
    Set<Pair<Character, String>> outgoing = new HashSet<>();
    for(Entry<Pair<String, Character>, Set<String>> entry : transitions.entrySet()) {
    	if(entry.getKey().getKey() == p) {
    		//found string
    		Character label = entry.getKey().getValue();
    		for(String dest : entry.getValue()) {
    		//loop through set of destinations
    			outgoing.add( new Pair<Character, String>(label, dest) );
    		}
    	    
    	}
    }
    return outgoing;
  }

  /**
   * Determinize an automaton.
   * 
   * @return An equivalent deterministic automaton.
   */
  @Override
  public DetAutomaton determinize () {
    // TODO: Fill this.
	  
	  DetAutomaton detAut = new DetAutomaton(alphabet);
	  detAut.setInitial(initialState);
	  for(String state : getFinal()) {
		  detAut.setFinal(state);
	  }
	  for(String state : getStates()) {
		  detAut.addState(state);
		  for(Pair<Character, String> pair : getTransitionsFrom(state)) {
			  if(pair.getKey() != EPSILON) {
				  detAut.addTransition(state, pair.getKey(), pair.getValue());
			  }
		  }
	  }
	  return detAut;
  }
}
