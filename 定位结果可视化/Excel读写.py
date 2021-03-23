import xlrd
def read_excel(file_name):
    data = xlrd.open_workbook(file_name)
    table = data.sheet_by_name("Sheet1")
    row_number = table.nrows
    row = []
    for i in range(row_number-1):
        row.append(table.row_values(i))
    return row

