import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

/**
 * A sample program that demonstrates how to execute SQL UPDATE statement
 * using JDBC.
 * @author www.codejava.net
 *
 */
public class Jdbc_homework1_4 {

	public static void main(String[] args) {
		String dbURL = "jdbc:mysql://localhost:3306/sample";
		String username = "root";
		String password = "0416";
		try  {
			Connection conn = DriverManager.getConnection(dbURL, username, password);

			String sql = "UPDATE building SET name=? WHERE name=?";

			PreparedStatement statement = conn.prepareStatement(sql);
			statement.setString(1, "정보통신관");
			statement.setString(2, "IT / BT");

			int rowsUpdated = statement.executeUpdate();
			if (rowsUpdated > 0) {
				System.out.println("An existing building was updated successfully!");
			}


		} catch (SQLException ex) {
			ex.printStackTrace();
		}
	}
}