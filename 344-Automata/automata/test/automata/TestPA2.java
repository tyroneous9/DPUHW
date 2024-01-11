package automata;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.StringWriter;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Arrays;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;

import org.xml.sax.SAXException;

import automata.Automaton.AutomatonBuilder;
import automata.Test.TestException;

public class TestPA2<DetAut extends Automaton, Aut extends Automaton & Automaton.NonDeterminism<DetAut>> {
  private AutomatonBuilder<DetAut> detbuilder;
  private AutomatonBuilder<Aut> builder;

  public TestPA2 (AutomatonBuilder<DetAut> detbuilder_,
      AutomatonBuilder<Aut> builder_) {
    builder = builder_;
    detbuilder = detbuilder_;
  }

  private <AnyAut extends Automaton>
      void testAutIO (AnyAut A, File f, String extraInfo, Double... d) throws IOException, TestException {
    double value = d.length > 0 ? d[0] : 0;
    for (String s : Files.readAllLines (Paths.get (f.getAbsolutePath ().replace (".xml", "-in.txt"))))
      if (!A.accepts (s))
        throw new TestException ("word " + s + " wrongly rejected" + extraInfo, value);

    for (String s : Files.readAllLines (Paths.get (f.getAbsolutePath ().replace (".xml", "-out.txt"))))
      if (A.accepts (s))
        throw new TestException ("word " + s + " wrongly accepted" + extraInfo, value);
  }

  private void testFile (File f, boolean noDeterminize) throws TestException {
    try {
      Aut A = XML.fromXMLFile (f.getAbsolutePath (), builder);

      if (A.isDeterministic ())
        throw new TestException ("automaton appears to be deterministic or works on wrong alphabet.");

      // Test accepted/rejected words.
      testAutIO (A, f, " (wrong accepts())");

      // Test that the automaton can be reconstructed.
      ByteArrayOutputStream outxml = new ByteArrayOutputStream ();
      XML.toXML (A, outxml);
      ByteArrayInputStream inxml = new ByteArrayInputStream (outxml.toByteArray ());
      Aut B = XML.fromXML (inxml, builder);
      if (!A.equals (B))
        throw new TestException ("failed to be put into XML and back (faulty getTransitionsFrom).", 0.3);

      if (noDeterminize)
        return;

      DetAut Adet = XML.fromXMLFile (f.getAbsolutePath ().replace (".xml", "-det.xml"), detbuilder);
      DetAut Bdet = A.determinize ();

      testAutIO (Bdet, f, " on the determinized.", 0.6);
      Bdet = Bdet.trim (detbuilder).minimize (detbuilder);
      if (Bdet == null) {
        throw new TestException ("determinized is either not deterministic or not complete.", 0.6);
      }
      testAutIO (Bdet, f, " on the determinized, then minimized.", 0.6);
      

      if (!Adet.isEquivalentMinimal (Bdet))
        throw new TestException ("determinized version is not the one expected.", 0.8);
      
    } catch (ParserConfigurationException | SAXException | IOException | TransformerException e) {
      StringWriter sw = new StringWriter ();
      e.printStackTrace (new PrintWriter (sw));
      throw new TestException ("FATAL: " + sw.toString ());
    }
  }

  public void runTests () {
    runTests (1, false);
  }

  public boolean runTests (int inc, boolean noDeterminize) {
    int totalTests = 0;
    double score = 0.;
    File dir = new File ("test/resources/");
    File[] files = dir.listFiles ( (d, name) -> name.startsWith ("naut-") &&
        name.endsWith (".xml") && !name.contains ("det"));
    Arrays.sort (files);

    int skip = 0;
    for (File f : files) {
      if (++skip == inc)
        skip = 0;
      else
        continue;
      totalTests++;
      score += Test.runTest (f.getName (), () -> { testFile (f, noDeterminize); return null; }, 1);
    }

    System.err.println ("SCORE: " + Math.round (score) + "/" + totalTests);
    return Math.round (score) == totalTests;
  }

  public void benchmarkDeterminize (String id) {
    Test.StopWatch stopwatch = new Test.StopWatch ();
    System.err.println ("NOTE: You need to score full points on the first part to obtain bonus points.");
    System.err.println ("Running a few of the tests");
    if (!runTests (12, false)) {
      System.err.println ("FAILED.");
      return;
    }

    try {
      System.err.println ("Loading large automaton");
      Aut A = XML.fromXMLFile ("test/resources/naut-largedet.xml", builder);
      stopwatch.start ();
      int ndet = 4;
      for (int i = 0; i < ndet; ++i) {
        System.err.println ("Determinization " + (i + 1) + " of " + ndet);
        A.determinize ();
      }
      stopwatch.stop ();
      System.err.println ("AVERAGE TIME IN MS (UID: " + id + "): " + stopwatch.duration () / ndet);
    } catch (ParserConfigurationException | SAXException | IOException e) {
      e.printStackTrace ();
    }

  }

  static public void main (String[] args) {
    TestPA2<DetAutomaton, NonDetAutomaton> t2 = new TestPA2<> (s -> new DetAutomaton (s),
                                                               s -> new NonDetAutomaton (s));
    if (args.length == 0)
      t2.runTests (2, false);
    else
      t2.benchmarkDeterminize (args[0]);
    System.exit (0);
  }
}
