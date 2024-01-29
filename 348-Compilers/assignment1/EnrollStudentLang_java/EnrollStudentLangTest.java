import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class EnrollStudentLangTest {

    @Test
    void testParseFailRecursive() throws Exception {
        TokenStream mockStream = createMockStream("Fail the prereq. Bomb the proficiency exam.");
        assertDoesNotThrow(() -> EnrollStudentLang.parseFail(mockStream));
    }

    @Test
    void testParseFailSuccess() throws Exception {
        TokenStream mockStream = createMockStream("bomb the proficiency exam.");
        assertDoesNotThrow(() -> EnrollStudentLang.parseFail(mockStream));
    }

    @Test
    void testParseFailException() throws Exception {
        TokenStream mockStream = createMockStream("unexpected input");
        assertThrows(Exception.class, () -> EnrollStudentLang.parseFail(mockStream));
    }

    @Test
    void testParseSucceedSuccess() throws Exception {
        TokenStream mockStream = createMockStream("Ace the proficiency exam. Attend the class.");
        assertDoesNotThrow(() -> EnrollStudentLang.parseSucceed(mockStream));
    }

    // Helper method to create a mock TokenStream
    private TokenStream createMockStream(String input) throws Exception {
        // Implementation to create a mock TokenStream based on the input
        return new TokenStream(new InputCharStream(input));
    }
}
