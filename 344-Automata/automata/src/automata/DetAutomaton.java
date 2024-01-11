package automata;

import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;
import java.util.stream.Collectors;

import javax.swing.text.html.HTMLDocument.Iterator;

/**
 * Implementation of deterministic automata.
 */
public class DetAutomaton extends Automaton {
  // from state, alphabet letter, to state
  private Map<Pair<String, Character>, String> transitions;
  private Set<Character> alphabet;
  private Set<String> states;
  private Set<String> final_states;
  private String initial_state;
  
  /**
   * Create an automaton on a given alphabet.
   * 
   * @param alph The alphabet of the automaton, can be EMPTY_SET.
   */
  public DetAutomaton (Set<Character> alph) {
    // TODO: Fill this.
    transitions = new HashMap<Pair<String, Character>, String>();
    this.alphabet = new HashSet<>(alph);
    states = new HashSet<>();
    final_states = new HashSet<>();
    initial_state = "";
  }

  /**
   * Create an automaton on a given alphabet.
   * 
   * @param alph The alphabet of the automaton, as a String, each character
   *             being a letter of the alphabet.
   */
  public DetAutomaton (String alph) {
    // Converts a string to a set of character. Do not touch.
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
   * @param label Label of the transition.
   * @param q     State to which the transition goes.
   */
  @Override
  public void addTransition (String p, char label, String q) {
    // TODO: Fill this.
    transitions.put( new Pair<>(p,label), q );
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
    String currState = initial_state;
    for(Character label : w.toCharArray()) {
        currState = transitions.get( new Pair<String, Character>(currState, label) );
    }
    if(final_states.contains(currState))
    	return true;
    return false;
  }

  /**
   * Set a state to be final.
   * 
   * @param q State to add to the set of final states.
   */
  @Override
  public void setFinal (String q) {
    // TODO: Fill this.
    final_states.add(q);
  }

  /**
   * Return the set of final states.
   * 
   * @return The set of final states.
   */
  @Override
  public Set<String> getFinal () {
    // TODO: Fill this.
    return final_states;
  }

  /**
   * Set a state to be initial.
   * 
   * @param q The state to set as initial.
   */
  @Override
  public void setInitial (String q) {
    // TODO: Fill this.
    initial_state = q;
  }

  /**
   * Get the initial state.
   * 
   * @return The initial state.
   */
  @Override
  public String getInitial () {
    // TODO: Fill this.
    return initial_state;
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
    Set<Pair<Character, String>> outgoing = new HashSet<Pair<Character, String>>();
    for(Entry<Pair<String, Character>, String> entry : transitions.entrySet()) {
    	if(entry.getKey().getKey() == p) {
    		Character label = entry.getKey().getValue();
    	    outgoing.add( new Pair<Character, String>(label, entry.getValue()) );
    	}
    	
    }
    return outgoing;
  }

  /**
   * Complete the automaton in place, adding a new state only if necessary.
   */
  @Override
  public void complete () {
    // TODO: Fill this. (BONUS)
	  //check if complete
	  String sink_state = "#SINK";
	  if(states.contains(sink_state))
		  return;
	  boolean complete = true;
	  for(String state : states) {
		  for(Character label : alphabet) {
			  if(!transitions.containsKey(new Pair<String, Character>(state, label))) {
				  complete = false;
				  break;
			  }
		  }
		  if(complete==false)
			  break;
	  }
	  
	  //add sink state
	  addState(sink_state);
	  for(Character label : alphabet) {
		  addTransition(sink_state, label, sink_state);
	  }
	  //connect missing transitions to sink state	  
	  for(String state : states) {
		  for(Character label : alphabet) {
			  if(!transitions.containsKey(new Pair<String, Character>(state, label))) {
				  addTransition(state, label, sink_state);
			  }
		  }
	  }
	  complete = true;
  }
  
}
