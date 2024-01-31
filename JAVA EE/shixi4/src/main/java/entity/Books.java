package entity;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.Date;
@NoArgsConstructor
@Data
public class Books {
    private Integer id;
    private String bookName;
    private String author;
    private Double price;
    private String press;
    private Date pressDate;

    public Books(String bookName, String author, Double price, String press) {
        this.bookName = bookName;
        this.author = author;
        this.price = price;
        this.press = press;
    }
}
