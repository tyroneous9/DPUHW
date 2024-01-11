package automata;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.Set;
import java.util.function.Supplier;
import java.util.stream.Collectors;

import javax.xml.parsers.ParserConfigurationException;

import org.xml.sax.SAXException;

import com.google.re2j.Pattern;

import automata.Automaton.AutomatonBuilder;
import automata.Test.TestException;

public class TestPA3<DetAut extends Automaton, NonDetAut extends Automaton & Automaton.NonDeterminism<DetAut>,
    RE extends Automaton.RegExpConverter<DetAut, NonDetAut>> {
  private AutomatonBuilder<NonDetAut> builder;
  private Supplier<RE> rebuilder;

  public TestPA3 (AutomatonBuilder<DetAut> detbuilder_,
      AutomatonBuilder<NonDetAut> builder_,
      Supplier<RE> rebuilder_) {
    builder = builder_;
    rebuilder = rebuilder_;
  }

  void testAutIO (NonDetAut A, File f) throws IOException, TestException {
    for (String s : Files.readAllLines (Paths.get (f.getAbsolutePath ().replaceAll ("\\.[^.]*$", "-in.txt"))))
      if (!A.accepts (s))
        throw new TestException ("word " + s + " wrongly rejected");

    for (String s : Files.readAllLines (Paths.get (f.getAbsolutePath ().replaceAll ("\\.[^.]*$", "-out.txt"))))
      if (A.accepts (s))
        throw new TestException ("word " + s + " wrongly accepted");
  }

  private void testFileRegExpToNFA (File f) throws TestException {
    // Strategy: Read the regExp, test words in and out, so as not to depend on the
    // correctness of determinize().
    try {
      RE re = rebuilder.get ();
      String filecontent = Files.readAllLines (f.toPath ()).stream ().findFirst ().orElse ("");
      String alphabet = filecontent.split (":")[0];
      String regexp = filecontent.split (":")[1];
      Set<Character> alphSet = alphabet.chars ().mapToObj (e -> (char) e).collect (Collectors.toSet ());

      NonDetAut A = re.regExpToNFA (regexp, alphSet);

      testAutIO (A, f);
    } catch (IOException e1) {
    	e1.printStackTrace ();
    }
  }

  private void testFileNFAToRegExp (File f) throws TestException {
    // Strategy: Use the regexp, translate it to Java regexp, and tests words
    // in/out.
    try {
      NonDetAut A = XML.fromXMLFile (f.getAbsolutePath (), builder);
      RE re = rebuilder.get ();
      String regexp = re.NFAToRegExp (A);
      Pattern p = Pattern.compile (regexp
          .replace ("" + Automaton.EPSILON, "()"));
      for (String s : Files.readAllLines (Paths.get (f.getAbsolutePath ().replaceAll ("\\.[^.]*$", "-in.txt")))) {
        if (!p.matcher (s).matches ())
          throw new TestException ("word " + s + " wrongly rejected");
      }

      for (String s : Files.readAllLines (Paths.get (f.getAbsolutePath ().replaceAll ("\\.[^.]*$", "-out.txt"))))
        if (p.matcher (s).matches ())
          throw new TestException ("word " + s + " wrongly accepted");
    } catch (IOException | ParserConfigurationException | SAXException e) {
    }
  }

  double runTestsRegExpToNFA () {
    int totalTests = 0;
    int passedTests = 0;
    File dir = new File ("test/resources/");
    File[] files =
        dir.listFiles ( (d, name) -> name.startsWith ("regexp-") &&
            !name.contains ("in") && !name.contains ("out"));
    Arrays.sort (files);

    for (File f : files) {
      totalTests++;
      if (Test.runTest (f.getName (), () -> {
        testFileRegExpToNFA (f);
        return null;
      }, 1) == 1.)
        passedTests++;
    }

    System.err.println ("SCORE regExpToNFA: " + passedTests + "/" + totalTests);
    return (double) passedTests / totalTests;
  }

  double runTestsNFAToRegExp () {
    int totalTests = 0;
    int passedTests = 0;
    File dir = new File ("test/resources/");
    File[] files =
        dir.listFiles ( (d, name) -> name.startsWith ("naut") &&
            name.endsWith (".xml") && !name.contains ("det") &&
            !name.contains ("in") && !name.contains ("out"));
    Arrays.sort (files);

    for (File f : files) {
      totalTests++;
      if (Test.runTest (f.getName (), () -> {
        testFileNFAToRegExp (f);
        return null;
      }, 1) == 1.)
        passedTests++;
    }

    System.err.println ("SCORE NFAToRegExp: " + passedTests + "/" + totalTests);
    return (double) passedTests / totalTests;
  }

  void runTests () {
    double d1 = runTestsRegExpToNFA ();
    double d2 = runTestsNFAToRegExp ();

    int score = (int) Math.ceil ( (d1 + d2) * 100);
    System.err.println ("SCORE: " + score + "/100");
  }
  
  static public void main (String[] args) {
    TestPA3<DetAutomaton, NonDetAutomaton,
        RegExp> t3 = new TestPA3<> (s -> new DetAutomaton (s),
            s -> new NonDetAutomaton (s),
            () -> new RegExp ());
    t3.runTests ();

    System.exit (0);
  }
}
