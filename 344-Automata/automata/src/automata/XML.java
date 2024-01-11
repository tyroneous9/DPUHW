package automata;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import automata.Automaton.AutomatonBuilder;

/**
 * Some utility functions, mostly pertaining to XML at this point.
 */
public class XML {

  /**
   * @param stream Input stream of an XML document
   * @return The automaton described by the XML document. The format is:
   * 
   *         <pre>
   * {@code
   *         <automaton alphabet="ab">
   *         <state name="q1" initial="true">
   *         <transition to="q2" label="b"/>
   *         <transition to="q1" label="a"/>
   *         </state>
   *         <state name="q2" final="true">
   *         <transition to="q1" label="b"/>
   *         <transition to="q2" label="a"/>
   *         </state>
   *         </automaton>}
   * </pre>
   * 
   * @throws ParserConfigurationException
   * @throws SAXException
   * @throws IOException
   */
  static public <Aut extends Automaton>
      Aut fromXML (InputStream stream, AutomatonBuilder<Aut> builder)
          throws ParserConfigurationException, SAXException, IOException {
    // Parse document
    DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance ();
    DocumentBuilder dBuilder = dbFactory.newDocumentBuilder ();
    Document doc = dBuilder.parse (stream);
    doc.getDocumentElement ().normalize ();

    // Get alphabet from root
    Element root = doc.getDocumentElement ();
    Aut A = builder.build (root.getAttribute ("alphabet"));

    // Add all states.
    NodeList states = doc.getElementsByTagName ("state");
    for (int i = 0; i < states.getLength (); ++i) {
      Element state = (Element) states.item (i);
      A.addState (state.getAttribute ("name"));
    }

    // Add transitions.
    for (int i = 0; i < states.getLength (); ++i) {
      Element state = (Element) states.item (i);
      String stateName = state.getAttribute ("name");
      NodeList transitions = state.getElementsByTagName ("transition");
      for (int j = 0; j < transitions.getLength (); ++j) {
        Element transition = (Element) transitions.item (j);
        A.addTransition (stateName, transition.getAttribute ("label").charAt (0),
            transition.getAttribute ("to"));
      }
      if (state.hasAttribute ("initial") && state.getAttribute ("initial").equals ("true"))
        A.setInitial (stateName);
      if (state.hasAttribute ("final") && state.getAttribute ("final").equals ("true"))
        A.setFinal (stateName);
    }

    return A;
  }

  /**
   * @param filename XML file.
   * @return An automaton, see above for XML format.
   * @throws FileNotFoundException
   * @throws ParserConfigurationException
   * @throws SAXException
   * @throws IOException
   */
  static public <Aut extends Automaton>
      Aut fromXMLFile (String filename, AutomatonBuilder<Aut> builder)
          throws FileNotFoundException, ParserConfigurationException, SAXException, IOException {
    File fXmlFile = new File (filename);
    return fromXML (new FileInputStream (fXmlFile), builder);
  }

  /**
   * @param A      An automaton.
   * @param stream An output stream, XML will be written over there.
   * @throws TransformerException
   * @throws ParserConfigurationException
   */
  static public <Aut extends Automaton>
      void toXML (Aut A, OutputStream stream)
          throws TransformerException, ParserConfigurationException {
    // Create document.
    DocumentBuilderFactory documentFactory = DocumentBuilderFactory.newInstance ();
    DocumentBuilder documentBuilder = documentFactory.newDocumentBuilder ();
    Document document = documentBuilder.newDocument ();

    // Put alphabet in root.
    Element root = document.createElement ("automaton");
    document.appendChild (root);
    final StringBuilder alphabet = new StringBuilder ();
    A.getAlphabet ().forEach ( (l) -> alphabet.append (l));
    root.setAttribute ("alphabet", alphabet.toString ());

    // Go through states.
    for (String q : A.getStates ()) {
      // Fill the state element.
      Element state = document.createElement ("state");
      root.appendChild (state);
      state.setAttribute ("name", q);
      if (A.getInitial ().equals (q))
        state.setAttribute ("initial", "true");
      if (A.getFinal ().contains (q))
        state.setAttribute ("final", "true");

      // Go through outgoing transitions.
      for (Pair<Character, String> trans : A.getTransitionsFrom (q)) {
        Element transition = document.createElement ("transition");
        state.appendChild (transition);
        transition.setAttribute ("to", trans.getValue ());
        transition.setAttribute ("label", trans.getKey ().toString ());
      }
    }

    // Write to stream.
    TransformerFactory transformerFactory = TransformerFactory.newInstance ();
    Transformer transformer = transformerFactory.newTransformer ();
    DOMSource domSource = new DOMSource (document);
    StreamResult streamResult = new StreamResult (stream);
    transformer.setOutputProperty (OutputKeys.INDENT, "yes");
    transformer.setOutputProperty ("{http://xml.apache.org/xslt}indent-amount", "2");
    transformer.setOutputProperty (OutputKeys.OMIT_XML_DECLARATION, "yes");
    transformer.transform (domSource, streamResult);
  }

  /**
   * @param A        An automaton.
   * @param filename The filename of the XML file.
   * @throws FileNotFoundException
   * @throws TransformerException
   * @throws ParserConfigurationException
   */
  static public <Aut extends Automaton>
      void toXMLFile (Aut A, String filename)
          throws FileNotFoundException, TransformerException, ParserConfigurationException {
    File fXmlFile = new File (filename);
    toXML (A, new FileOutputStream (fXmlFile));
  }
}
