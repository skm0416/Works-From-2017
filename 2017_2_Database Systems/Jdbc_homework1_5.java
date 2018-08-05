import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

/**
 * A sample program that demonstrates how to execute SQL SELECT statement
 * using JDBC. 
 * @author www.codejava.net
 *
 */
public class Jdbc_homework1_5 {

	public static void main(String[] args) {
		String dbURL = "jdbc:mysql://localhost:3306/sample";
		String username = "root";
		String password = "0416";
		
		try  {
			Connection conn = DriverManager.getConnection(dbURL, username, password);
			String sql = "SELECT DISTINCT rooms.building_id, building.name FROM building, rooms "
					+ "WHERE rooms.occupancy>=100 AND rooms.building_id=building.id";
			
			Statement statement = conn.createStatement();
			ResultSet result = statement.executeQuery(sql);
			
			int count = 0;
			
			while (result.next()){
				String id = result.getString("building_id");
				String name = result.getString("name");
				
				String output = "Building #%d: %s - %s";
				System.out.println(String.format(output, ++count, id, name));
			}
			
		} catch (SQLException ex) {
			ex.printStackTrace();
		}		
	}
}