package automata;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Random;
import java.util.Set;
import java.util.Stack;
import java.util.stream.Collectors;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;

import automata.Automaton.AutomatonBuilder;

public class GenTests {

  // Get shortest word that is accepted (if accepted is true) from state p.
  static private <Aut extends Automaton>
      String getShortestWord (Aut A, String p, boolean accepted) {
    if (A.getFinal ().contains (p) == accepted)
      return "";

    Map<String, String> marked = new HashMap<> ();
    Stack<String> totreat = new Stack<> ();

    marked.put (p, "");
    totreat.add (p);
    while (!totreat.isEmpty ()) {
      String s = totreat.pop ();
      for (Pair<Character, String> pair : A.getTransitionsFrom (s)) {
        String t = pair.getValue ();
        if (!marked.containsKey (t)) {
          String w = marked.get (s) + pair.getKey ();
          if (A.getFinal ().contains (t) == accepted)
            return w;
          marked.put (t, w);
          totreat.push (t);
        }
      }
    }
    return null;
  }

  static private Set<String> genWords (DetAutomaton A, int nwords, int approxLength, boolean accepted) {
    Set<String> states = A.getStates ();
    Map<String, String> shortestWords = new HashMap<> ();

    // Compute shortest @accepted words from each state.
    states.forEach (p -> {
      String shorts = getShortestWord (A, p, accepted);
      if (shorts != null)
        shortestWords.put (p, shorts);
    });

    if (!shortestWords.containsKey (A.getInitial ()))
      return Collections.emptySet ();

    Set<String> res = new HashSet<> (nwords);
    while (nwords-- > 0) {
      StringBuilder word = new StringBuilder ();
      // Start wandering.
      String curState = A.getInitial ();
      for (int i = 0; i < approxLength; ++i) {
        Set<Pair<Character, String>> neighbours = A.getTransitionsFrom (curState);
        neighbours.removeIf (pair -> !shortestWords.containsKey (pair.getValue ()));
        if (neighbours.isEmpty ()) // Dead end!
          break;
        Pair<Character, String> next =
            neighbours.stream ()
                .skip (new Random ().nextInt (neighbours.size ()))
                .findFirst ().orElse (null);
        word.append (next.getKey ());
        curState = next.getValue ();
        if (i + shortestWords.get (curState).length () > approxLength)
          break;
      }
      word.append (shortestWords.get (curState));
      res.add (word.toString ());
    }
    return res;
  }

  static private <Aut extends Automaton>
      Aut genAutomaton (String alphabet, int nstates, double finals,
          boolean complete, boolean deterministic, AutomatonBuilder<Aut> builder) {
    Aut A = builder.build (alphabet);
    Random rnd = new Random ();
    boolean incomplete = false,
        nondeterministic = false;

    for (int i = 0; i < nstates; ++i) {
      A.addState ("q" + i);
      if (rnd.nextDouble () < finals)
        A.setFinal ("q" + i);
    }
    A.setInitial ("q0");
    for (int i = 0; i < nstates; ++i) {
      for (char c : alphabet.toCharArray ())
        if (complete || rnd.nextDouble () < 0.9) {
          int next = rnd.nextInt (nstates);
          A.addTransition ("q" + i, c, "q" + next);
          if (!deterministic && rnd.nextDouble () < 0.3) {
            int other;
            do {
              other = rnd.nextInt (nstates);
            } while (other == next);
            if (rnd.nextDouble () > 0.7)
              c = Automaton.EPSILON;
            A.addTransition ("q" + i, c, "q" + other);
            nondeterministic = true;
          }
        } else
          incomplete = true;
    }

    // Make sure it's incomplete if asked.
    if (!complete && !incomplete)
      A.addState ("q" + nstates);

    // Same with determinism.
    if (!deterministic && !nondeterministic) {
      Set<Pair<Character, String>> neiglist = A.getTransitionsFrom ("q0");
      if (neiglist.isEmpty ()) {
        A.addTransition ("q0", alphabet.charAt (0), "q0");
        A.addTransition ("q0", alphabet.charAt (0), "q1");
      } else {
        Pair<Character, String> trans = neiglist.iterator ().next ();
        String other = (trans.getValue ().equals ("q0") ? "q1" : "q0");
        A.addTransition ("q0", trans.getKey (), other);
      }
    }

    return A;
  }

  static public <Aut extends Automaton>
      void testWord (Aut A, String... W) {
    for (String w : W)
      System.out.println ("A on " + w + ": " + A.accepts (w));
  }

  static void writeGenWordsToFile (DetAutomaton A, int nwords, int length,
      boolean accept, String filename) {
    try {
      File out = new File (filename);
      FileOutputStream outstream = new FileOutputStream (out);
      for (String w : genWords (A, nwords, length, accept)) {
        outstream.write (w.getBytes ());
        outstream.write ('\n');
      }
      outstream.close ();

    } catch (IOException e) {
      e.printStackTrace ();
    }

  }

  // DFA DB
  static private void genDFAXMLInOut (int nstates, String filename, boolean complete) {
    String[] alphabets = { "ab", "ab", "abc", "abcd" };
    Random rnd = new Random ();
    DetAutomaton A = genAutomaton (alphabets[rnd.nextInt (alphabets.length)],
        nstates, rnd.nextDouble () / 3, complete, true, alph -> new DetAutomaton (alph));
    try {
      XML.toXMLFile (A, filename + ".xml");
      if (!complete)
        A.complete ();
    } catch (IOException | TransformerException | ParserConfigurationException e) {
      e.printStackTrace ();
    }
    writeGenWordsToFile (A, 100, rnd.nextInt (100) + 10, true, filename + "-in.txt");
    writeGenWordsToFile (A, 100, rnd.nextInt (100) + 10, false, filename + "-out.txt");
  }

  static public void genDFADB () {
    for (int i = 1; i <= 100; ++i)
      for (int j = 0; j < 3; ++j) {
        String filename = "test/resources/aut-" + i + "-" + j;
        genDFAXMLInOut (i, filename, true);
      }
    for (int i = 30; i < 80; i += 2)
      for (int j = 0; j < 2; ++j) {
        String filename = "test/resources/incomplete-aut-" + i + "-" + j;
        genDFAXMLInOut (i, filename, false);
      }
  }

  static private void genNFAXMLInOut (int nstates, boolean enforceNonEmpty, String filename) {
    String[] alphabets = { "ab", "ab", "abc", "abcd" };
    Random rnd = new Random ();
    NonDetAutomaton A = genAutomaton (alphabets[rnd.nextInt (alphabets.length)],
        nstates, rnd.nextDouble () / 3, false, false, alph -> new NonDetAutomaton (alph));
    if (enforceNonEmpty && getShortestWord (A, "q0", true) == null)
      A.setFinal ("q0");
    DetAutomaton Adet = A.determinize ().minimize (alph -> new DetAutomaton (alph));
    try {
      XML.toXMLFile (A, filename + ".xml");
      XML.toXMLFile (Adet, filename + "-det.xml");
    } catch (IOException | TransformerException | ParserConfigurationException e) {
      e.printStackTrace ();
    }
    writeGenWordsToFile (Adet, 100, rnd.nextInt (100) + 10, true, filename + "-in.txt");
    writeGenWordsToFile (Adet, 100, rnd.nextInt (100) + 10, false, filename + "-out.txt");
  }

  static public void genNFADB () {
    for (int i = 2; i <= 9; ++i) { // Careful: Shouldn't have just one state.
      System.out.println (i);
      for (int j = 0; j < 10 + (i == 5 || i == 7 ? 10 : 0); ++j) {
        String filename = "test/resources/naut-" + i + "-" + j;
        genNFAXMLInOut (i, true, filename);
      }
    }
  }

  static public void genNFABonus () {
    // Generate bonus.
    NonDetAutomaton A = genAutomaton ("abcd", 22, 0.2, false, false,
        alph -> new NonDetAutomaton (alph));
    try {
      XML.toXMLFile (A, "test/resources/naut-largedet.xml");
    } catch (Exception e) {
      e.printStackTrace ();
    }
  }

  // Generating RE.
  static private String genRE (int approxlength, String alphabet) {
    Random rnd = new Random ();
    StringBuilder sb = new StringBuilder ();
    while (approxlength > sb.length ()) {
      // Generate a block: either a epsilon, or a concat of letters and subexps
      double type = rnd.nextDouble ();
      if (type < 0.1) {
        sb.append (Automaton.EPSILON);
        approxlength--;
      } else {
        type /= 2; // This is to be sure we produce something.
        while (approxlength > sb.length ()) {
          if (type > 0.5)
            break;
          if (type < 0.2) {
            int newLen = rnd.nextInt (approxlength - sb.length ());
            String subexp = genRE (newLen + 1, alphabet);
            sb.append ("(" + subexp + ")");
          } else {
            int letter = rnd.nextInt (alphabet.length () + 1);
            if (letter == alphabet.length ())
              sb.append (Automaton.EPSILON);
            else
              sb.append (alphabet.charAt (letter));
          }
          type = rnd.nextDouble ();
          if (type > 0.4)
            sb.append ("*");
          type = rnd.nextDouble ();
        }
      }
      // Not the last block: Add a +.
      if (approxlength > sb.length ()) {
        sb.append ("|");
        approxlength++; // Make sure we generate another block
      }
    }
    return sb.toString ();
  }

  static private void genREInOut (int approxlength, String filename) {
    String[] alphabets = { "ab", "ab", "abc", "abcd" };
    Random rnd = new Random ();
    String alphabet = alphabets[rnd.nextInt (alphabets.length)];
    String regexp = genRE (approxlength, alphabet);
    Set<Character> alphSet = alphabet.chars ().mapToObj (e -> (char) e).collect (Collectors.toSet ());
    RegExp re = new RegExp ();

    DetAutomaton A = re.regExpToNFA (regexp, alphSet).determinize ();
    writeGenWordsToFile (A, 100, rnd.nextInt (100) + 10, true, filename + "-in.txt");
    writeGenWordsToFile (A, 100, rnd.nextInt (100) + 10, false, filename + "-out.txt");
    File out = new File (filename + ".txt");
    FileOutputStream outstream;
    try {
      outstream = new FileOutputStream (out);
      outstream.write ( (alphabet + ":" + regexp).getBytes ());
      outstream.close ();
    } catch (IOException e1) {
      e1.printStackTrace ();
    }
  }

  static public void genRegExps () {
    for (int i = 5; i <= 50; i += 5) {
      System.out.println (i);
      for (int j = 0; j < 10; ++j) {
        String filename = "test/resources/regexp-" + i + "-" + j;
        genREInOut (i, filename);
      }
    }
  }

  static public void genRegExpsFromNFADB () {
    File dir = new File ("test/resources/");
    File[] files = dir.listFiles ( (d, name) -> name.startsWith ("naut-9-17") &&
        name.endsWith (".xml") && !name.contains ("det"));
    RegExp re = new RegExp ();
    try {
      for (File f : files) {
        System.out.println (f.getAbsolutePath ());
        NonDetAutomaton A = XML.fromXMLFile (f.getAbsolutePath (),
            s -> new NonDetAutomaton (s));
        String regexp = re.NFAToRegExp (A);
        File out = new File (f.getAbsolutePath ().replace (".xml", "-re.txt"));
        FileOutputStream outstream = new FileOutputStream (out);
        outstream.write (regexp.getBytes ());
        outstream.close ();
        System.out.println (f.getAbsolutePath ());
        DetAutomaton A1 = A.determinize ().minimize (s -> new DetAutomaton (s));
        System.out.println (f.getAbsolutePath ());

        DetAutomaton A2 =
            re.regExpToNFA (regexp, A.getAlphabet ()).determinize ()
                .minimize (s -> new DetAutomaton (s));
        System.out.println (f.getAbsolutePath ());
        assert (A1.isEquivalentMinimal (A2));

      }
    } catch (Exception e) {
      e.printStackTrace ();
    }
  }

  public static void main (String[] args) {
    // genDFADB ();
    //genNFADB ();
    genNFABonus ();
    // genRegExpsFromNFADB ();
    // genRegExps ();
  }
}
