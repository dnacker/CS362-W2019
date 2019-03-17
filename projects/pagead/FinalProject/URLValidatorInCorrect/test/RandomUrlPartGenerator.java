import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.regex.Pattern;

/**
 * This class generates ranodom valid and invalid components of a Url.
 */
public class RandomUrlPartGenerator {
    /**
     * A regex pattern matcher for a valid scheme.
     */
    private static final Pattern VALID_SCHEME = Pattern.compile("^([a-z][a-z0-9+\\-.]*)");

    private static final List<Character> alphaCharacters = Arrays.asList('a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z');

    private static final List<Character> numericCharacters = Arrays.asList('0', '1', '2', '3', '4', '5', '6', '7', '8', '9');

    /**
     * A list of general delimiter characters.
     */
    private static final List<Character> generalDelimiters = Arrays.asList(':', '/', '?', '#', '[', ']', '@');

    /**
     * A list of sub delimiter characters.
     */
    private static final List<Character> subDelimiters = Arrays.asList('!', '$', '&', '\'', '(', ')', '*', '+', ',', ';', '=');

    /**
     * A list of characters that can be in a scheme. These are defined here: https://tools.ietf.org/html/rfc3986#section-3.1
     */
    private static final List<Character> schemeCharacters = new ArrayList<>();

    /**
     * A list of characters that can be in a userInfo section. These are defined here: https://tools.ietf.org/html/rfc3986#section-3.2.1
     */
    private static final List<Character> userInfoCharacters = new ArrayList<>();

    /**
     * A list of unreserved characters. These are defined here: https://tools.ietf.org/html/rfc3986#section-2.3
     */
    private static final List<Character> unreservedCharacters = new ArrayList<>();

    /**
     * A list of reserved characters. These are defined here: https://tools.ietf.org/html/rfc3986#section-2.2
     */
    private static final List<Character> reservedCharacters = new ArrayList<>();

    /**
     * A list of registry name characters. These are defined here: https://tools.ietf.org/html/rfc3986#section-3.2.2
     */
    private static final List<Character> registryNameCharacters = new ArrayList<>();

    public RandomUrlPartGenerator() {
        schemeCharacters.addAll(alphaCharacters);
        schemeCharacters.addAll(numericCharacters);
        schemeCharacters.add('+');
        schemeCharacters.add('-');
        schemeCharacters.add('.');

        unreservedCharacters.addAll(schemeCharacters);
        unreservedCharacters.add('~');
        unreservedCharacters.add('_');

        reservedCharacters.addAll(generalDelimiters);
        reservedCharacters.addAll(subDelimiters);

        userInfoCharacters.addAll(unreservedCharacters);
        userInfoCharacters.addAll(subDelimiters);
        userInfoCharacters.add(':');

        registryNameCharacters.addAll(unreservedCharacters);
        registryNameCharacters.addAll(subDelimiters);
    }

    /**
     * Generates a valid url scheme. Definition: ALPHA *( ALPHA / DIGIT / "+" / "-" / "." )
     * @return a valid url scheme.
     */
    public String getValidScheme() {
        StringBuilder sb = new StringBuilder();
        int length = (int)(Math.random() * 10 + 1); // generate a random length from 1 - 10

        // First character must be alphabetic
        char first;
        do {
            first = getRandomCharacterFromList(schemeCharacters);
        } while (!Character.isAlphabetic(first));
        sb.append(first);

        for (; length > 0; length--) {
            // Random character from schemeCharacters list.
            sb.append(getRandomCharacterFromList(schemeCharacters));
        }

        return sb.toString();
    }

    /**
     * Generates an invalid url scheme.
     * @return an invalid url scheme.
     */
    public String getInvalidScheme() {
        StringBuilder sb = new StringBuilder();
        int length = (int)(Math.random() * 10 + 1);
        String result;
        boolean isInvalid = false;
        do {
            for (; length >= 0; length--) {
                sb.append((char) (Math.random() * Character.MAX_VALUE));
            }

            result = sb.toString();
            if (VALID_SCHEME.matcher(result).matches()) {
                sb = new StringBuilder();
            } else {
                isInvalid = true;
            }
        } while (!isInvalid);
        return result;
    }

    /**
     * Generates a valid authority.
     * @return a valid authority.
     */
    public String getValidAuthority() {
        StringBuilder sb = new StringBuilder();
        // has user information
        boolean hasUserInformation = (int)(Math.random() * 10) == 0; //10% of authorities have userInfo
        if (hasUserInformation) {
            sb.append(getUserInformation());
            sb.append("@");
        }
        boolean hasRegistryName = (int)(Math.random() * 10) > 0; //90% of authorities have registry names
        if (hasRegistryName) {
            sb.append(getRegName());
        } else {
            sb.append(getIpv4Address());
        }
        boolean hasPort = (int)(Math.random() * 10) == 0; // 10% of authorities have ports
        if (hasPort) {
            sb.append(":");
            sb.append(getPort());
        }

        return sb.toString();
    }

    /**
     * Generates an invalid authority.
     * @return an invalid authority.
     */
    public String getInvalidAuthority() {
        StringBuilder sb = new StringBuilder();
        int length = (int)(Math.random() * 100);
        for (; length >= 0; length--) {
            sb.append((char) (Math.random() * Character.MAX_VALUE));
        }

        return sb.toString();
    }

    private String getUserInformation() {
        StringBuilder sb = new StringBuilder();
        int length = (int)(Math.random() * 10 + 1);

        for (; length >= 0; length--) {
            sb.append(getRandomCharacterFromList(userInfoCharacters));
        }
        return sb.toString();
    }

    private String getIpv4Address() {
        StringBuilder sb = new StringBuilder();
        // Format is "[0-255].[0-255].[0-255].[0-255]"
        for (int i = 0; i < 4; i++) {
            sb.append((int)(Math.random() * 256));
            if (i != 3)
                sb.append('.');
        }
        return sb.toString();
    }

    private String getRegName() {
        StringBuilder sb = new StringBuilder();
        int length = (int) (Math.random() * 10 + 1);
        for (; length >= 0; length--) {
            sb.append(getRandomCharacterFromList(registryNameCharacters));
        }
        return sb.toString();
    }

    /**
     * Returns a random port from 0 - 65535.
     * @return a random port from 0 - 65535.
     */
    private String getPort() {
        return String.valueOf((int)(Math.random() * Math.pow(2, 16)));
    }

    private static char getRandomCharacterFromList(List<Character> list) {
        char randomChar = list.get((int)(Math.random()* list.size()));
        boolean isUpperCase = (int) (Math.random() * 2) == 0;
        if (isUpperCase && Character.isAlphabetic(randomChar)) {
            randomChar = Character.toUpperCase(randomChar);
        }
        return randomChar;
    }
}
