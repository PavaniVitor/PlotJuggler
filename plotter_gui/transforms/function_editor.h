#ifndef AddCustomPlotDialog_H
#define AddCustomPlotDialog_H

#include <QDialog>
#include <QListWidgetItem>
#include <unordered_map>
#include "PlotJuggler/plotdata.h"
#include "custom_function.h"
#include "qwt_plot_curve.h"
#include "ui_function_editor.h"

class FunctionEditorWidget : public QWidget
{
  Q_OBJECT

public:
  explicit FunctionEditorWidget(PlotDataMapRef& plotMapData, const CustomPlotMap& mapped_custom_plots, QWidget* parent);
  virtual ~FunctionEditorWidget() override;

  void setLinkedPlotName(const QString& linkedPlotName);

  enum EditorMode
  {
    FUNCTION_OR_TIMESERIES,
    TIMESERIES_ONLY,
    FUNCTION_ONLY
  };

  void clear();

  void setEditorMode(EditorMode mode);

  QString getLinkedData() const;
  QString getGlobalVars() const;
  QString getEquation() const;
  QString getName() const;

  const PlotData& getPlotData() const;
  void editExistingPlot(CustomPlotPtr data);
 // CustomPlotPtr getCustomPlotData() const;

  bool eventFilter(QObject *obj, QEvent *event) override;

private slots:

  void on_snippetsListSaved_currentRowChanged(int currentRow);

  void on_snippetsListSaved_doubleClicked(const QModelIndex& index);

  void on_nameLineEdit_textChanged(const QString& arg1);

  void savedContextMenu(const QPoint& pos);

  void on_buttonLoadFunctions_clicked();

  void on_buttonSaveFunctions_clicked();

  void on_pushButtonSave_clicked();

  void onRenameSaved();

  void on_pushButtonCreate_clicked();

  void on_pushButtonCancel_pressed();

  void on_listAdditionalSources_itemSelectionChanged();

  void on_pushButtonDeleteCurves_clicked();

  void on_listSourcesChanged();
  
  void on_lineEditSource_textChanged(const QString &text);

private:
  void importSnippets(const QByteArray& xml_text);

  QByteArray exportSnippets() const;

  bool addToSaved(const QString& name, const SnippetData& snippet);

  PlotDataMapRef& _plot_map_data;
  const CustomPlotMap& _custom_plots;
  Ui::FunctionEditor* ui;

  bool _is_new;
  int _v_count;

  SnippetsMap _snipped_saved;

  QStringList _dragging_curves;

signals:
  void accept(CustomPlotPtr plot);
  void closed();
};

#endif  // AddCustomPlotDialog_H
