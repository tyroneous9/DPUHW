import java.util.HashMap;
import java.util.Random;

public class UserManager {
    private static UserManager instance = new UserManager();
    private HashMap<String, User> users;

    private UserManager() {
        users = new HashMap<>();
    }

    public static UserManager getInstance() {
        return instance;
    }

    public void init(String[] usersIn) throws DataValidationException {
        for (String id : usersIn) {
            User user = new User(id);
            users.put(id, user);
        }
    }

    public User getUser(String id) {
        return users.get(id);
    }

    public User getRandomUser() {
        Random random = new Random();
        int stopIndex = random.nextInt(users.size());
        for(User user : users.values()) {
            if(stopIndex == 0) return user;
            stopIndex--;
        }
        //EXCEPTION HERE
        return null;
    }

    public void addToUser(String userId, OrderDTO o) throws OrderNotFoundException {
        User user = users.get(userId);
        user.addOrder(o);
    }

    @Override
    public String toString() {
        StringBuilder result = new StringBuilder();
        for (User user : users.values()) {
            result.append(user.toString()).append("\n");
        }
        return result.toString();
    }
}
